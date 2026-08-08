#include <stddef.h>
#include <stdint.h>

#include <carl/net/arp.h>

#define ARP_ENTRIES 4U

typedef struct {
    uint32_t ip;
    uint8_t mac[6];
} arp_entry_t;

static arp_entry_t g_arp_table[ARP_ENTRIES];

static void c_arp_populate_default_table(void) {
    g_arp_table[0].ip = 0xC0A80001U; /* 192.168.0.1 */
    g_arp_table[0].mac[0] = 0x00U;
    g_arp_table[0].mac[1] = 0x11U;
    g_arp_table[0].mac[2] = 0x22U;
    g_arp_table[0].mac[3] = 0x33U;
    g_arp_table[0].mac[4] = 0x44U;
    g_arp_table[0].mac[5] = 0x55U;

    g_arp_table[1].ip = 0xC0A8000AU; /* 192.168.0.10 */
    g_arp_table[1].mac[0] = 0x66U;
    g_arp_table[1].mac[1] = 0x77U;
    g_arp_table[1].mac[2] = 0x88U;
    g_arp_table[1].mac[3] = 0x99U;
    g_arp_table[1].mac[4] = 0xAAU;
    g_arp_table[1].mac[5] = 0xBBU;
}

void c_arp_init(void) {
    c_arp_populate_default_table();
}

int c_arp_resolve(uint32_t ip, uint8_t mac[6]) {
    if (mac == NULL) {
        return -1;
    }

    for (uint32_t i = 0; i < ARP_ENTRIES; ++i) {
        if (g_arp_table[i].ip == ip) {
            for (uint32_t j = 0; j < 6U; ++j) {
                mac[j] = g_arp_table[i].mac[j];
            }
            return 0;
        }
    }

    if (ip == 0xFFFFFFFFU) {
        for (uint32_t j = 0; j < 6U; ++j) {
            mac[j] = 0xFFU;
        }
        return 0;
    }

    return -1;
}
