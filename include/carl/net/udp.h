#ifndef CARL_NET_UDP_H
#define CARL_NET_UDP_H

#include <stdint.h>

void c_udp_init(void);

int c_udp_send(
    uint32_t ip,
    uint16_t port,
    void* data,
    uint32_t size
);

#endif /* CARL_NET_UDP_H */
