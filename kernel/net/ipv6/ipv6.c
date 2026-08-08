#include <stddef.h>
#include <stdint.h>

#include <carl/net/arp.h>
#include <carl/net/ethernet.h>
#include <carl/net/ipv6.h>

#define IPV6_VERSION 0x60000000U
#define IPV6_ETHERTYPE 0x86DDU

static uint8_t g_local_ipv6[16] = {
    0xFDU, 0x00U, 0x00U, 0x00U,
    0x00U, 0x00U, 0x00U, 0x00U,
    0x00U, 0x00U, 0x00U, 0x00U,
    0x00U, 0x00U, 0x00U, 0x01U
};

typedef struct {
    uint8_t destination_mac[6];
    uint8_t source_mac[6];
    uint16_t ethertype;
    ipv6_header_t ip;
} ipv6_packet_t;

void c_IPv6Init(void) {
    g_local_ipv6[0] = 0xFDU;
    g_local_ipv6[15] = 0x01U;
    c_arp_init();
}

int c_IPv6Send(
    const uint8_t destination[16],
    void *data,
    uint32_t size
) {
    uint8_t dst_mac[6];
    uint8_t packet[sizeof(ipv6_packet_t) + 1500U];
    ipv6_packet_t *payload;

    if (destination == NULL || data == NULL || size == 0U || size > 1500U) {
        return -1;
    }

    if (c_arp_resolve(0U, dst_mac) != 0) {
        return -1;
    }

    payload = (ipv6_packet_t *)packet;
    for (uint32_t i = 0; i < 6U; ++i) {
        payload->destination_mac[i] = dst_mac[i];
        payload->source_mac[i] = 0U;
    }

    payload->ethertype = IPV6_ETHERTYPE;
    payload->ip.version_traffic_flow = IPV6_VERSION;
    payload->ip.payload_length = (uint16_t)size;
    payload->ip.next_header = 0x3AU;
    payload->ip.hop_limit = 64U;

    for (uint32_t i = 0; i < 16U; ++i) {
        payload->ip.source_address[i] = g_local_ipv6[i];
        payload->ip.destination_address[i] = destination[i];
    }

    for (uint32_t i = 0; i < size; ++i) {
        ((uint8_t *)&payload->ip)[sizeof(ipv6_header_t) + i] = ((uint8_t *)data)[i];
    }

    return c_EthernetSend(dst_mac, payload->ethertype, &payload->ip, sizeof(ipv6_header_t) + size);
}
