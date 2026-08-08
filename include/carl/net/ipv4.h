#ifndef CARL_NET_IPV4_H
#define CARL_NET_IPV4_H

#include <stdint.h>

typedef struct {
    uint8_t version_ihl;      // Version (4 bits) + Internet Header Length (4 bits)
    uint8_t type_of_service;  // Type of Service
    uint16_t total_length;     // Total Length
    uint16_t identification;   // Identification
    uint16_t flags_fragment_offset; // Flags (3 bits) + Fragment Offset (13 bits)
    uint8_t time_to_live;      // Time to Live
    uint8_t protocol;          // Protocol
    uint16_t header_checksum;  // Header Checksum
    uint32_t source_address;   // Source Address
    uint32_t destination_address; // Destination Address
} ipv4_header_t;

void c_IPv4Init(void);

int c_IPv4Send(
    uint32_t destination,
    void *data,
    uint32_t size
);

#endif /* CARL_NET_IPV4_H */
