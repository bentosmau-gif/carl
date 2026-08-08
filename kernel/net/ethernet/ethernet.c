#include <stddef.h>
#include <stdint.h>

#include <carl/net/ethernet.h>

static uint8_t g_ethernet_mac[6] = {
    0x00U, 0x11U, 0x22U, 0x33U, 0x44U, 0x55U
};

void c_EthernetInit(void) {
    g_ethernet_mac[0] = 0x00U;
    g_ethernet_mac[1] = 0x11U;
    g_ethernet_mac[2] = 0x22U;
    g_ethernet_mac[3] = 0x33U;
    g_ethernet_mac[4] = 0x44U;
    g_ethernet_mac[5] = 0x55U;
}

int c_EthernetSend(
    uint8_t *destination_mac,
    uint16_t ethertype,
    void *data,
    uint32_t size
) {
    uint8_t frame[1518];
    uint32_t index;

    if (destination_mac == NULL || data == NULL) {
        return -1;
    }

    if (size > 1500U) {
        return -1;
    }

    for (index = 0; index < 6U; ++index) {
        frame[index] = destination_mac[index];
    }

    for (index = 0; index < 6U; ++index) {
        frame[6U + index] = g_ethernet_mac[index];
    }

    frame[12U] = (uint8_t)((ethertype >> 8) & 0xFFU);
    frame[13U] = (uint8_t)(ethertype & 0xFFU);

    for (index = 0; index < size; ++index) {
        frame[14U + index] = ((uint8_t *)data)[index];
    }

    (void)frame;
    return 0;
}

int c_EthernetReceive(
    ethernet_header_t *header
) {
    if (header == NULL) {
        return -1;
    }

    for (uint32_t i = 0; i < 6U; ++i) {
        header->destination_mac[i] = 0U;
        header->source_mac[i] = 0U;
    }

    header->ethertype = 0U;
    return 0;
}
