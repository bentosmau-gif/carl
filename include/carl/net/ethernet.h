#ifndef CARL_NET_ETHERNET_H
#define CARL_NET_ETHERNET_H

#include <stdint.h>

typedef struct {
    uint8_t destination_mac[6]; // Destination MAC Address
    uint8_t source_mac[6];      // Source MAC Address
    uint16_t ethertype;         // Ethertype field
} ethernet_header_t;

void c_EthernetInit(void);

int c_EthernetSend(
    uint8_t *destination_mac,
    uint16_t ethertype,
    void *data,
    uint32_t size
);

int c_EthernetReceive(
    ethernet_header_t *header
);

#endif /* CARL_NET_ETHERNET_H */
