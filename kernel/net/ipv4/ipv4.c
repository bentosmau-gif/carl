/* IPv4 implementation */

#include <stddef.h>
#include <stdint.h>

#include <carl/net/arp.h>
#include <carl/net/ethernet.h>
#include <carl/net/ipv4.h>

#define IPV4_VERSION 0x45U

typedef struct {
    uint8_t destination_mac[6];
    uint8_t source_mac[6];
    uint16_t ethertype;
    ipv4_header_t ip;
} ipv4_packet_t;

static uint32_t g_local_ip = 0xC0A8000AU; /* 192.168.0.10 */

void c_IPv4Init(void) {
    g_local_ip = 0xC0A8000AU;
    c_arp_init();
}

static uint16_t c_ipv4_checksum(const ipv4_header_t *header) {
    uint32_t sum = 0U;
    const uint16_t *words = (const uint16_t *)header;

    for (uint32_t i = 0; i < 10U; ++i) {
        sum += words[i];
    }

    while (sum >> 16) {
        sum = (sum & 0xFFFFU) + (sum >> 16);
    }

    return (uint16_t)(~sum & 0xFFFFU);
}

int c_IPv4Send(
    uint32_t destination,
    void *data,
    uint32_t size
) {
    uint8_t dst_mac[6];
    uint8_t packet[sizeof(ipv4_packet_t) + 1500U];
    ipv4_packet_t *payload;

    if (data == NULL || size == 0U || size > 1500U) {
        return -1;
    }

    if (c_arp_resolve(destination, dst_mac) != 0) {
        return -1;
    }

    payload = (ipv4_packet_t *)packet;
    for (uint32_t i = 0; i < 6U; ++i) {
        payload->destination_mac[i] = dst_mac[i];
        payload->source_mac[i] = 0U;
    }

    payload->ethertype = 0x0800U;
    payload->ip.version_ihl = IPV4_VERSION;
    payload->ip.type_of_service = 0U;
    payload->ip.total_length = (uint16_t)(sizeof(ipv4_header_t) + size);
    payload->ip.identification = 0U;
    payload->ip.flags_fragment_offset = 0U;
    payload->ip.time_to_live = 64U;
    payload->ip.protocol = 0x06U;
    payload->ip.header_checksum = 0U;
    payload->ip.source_address = g_local_ip;
    payload->ip.destination_address = destination;
    payload->ip.header_checksum = c_ipv4_checksum(&payload->ip);

    for (uint32_t i = 0; i < size; ++i) {
        ((uint8_t *)&payload->ip)[sizeof(ipv4_header_t) + i] = ((uint8_t *)data)[i];
    }

    return c_EthernetSend(dst_mac, payload->ethertype, &payload->ip, sizeof(ipv4_header_t) + size);
}
