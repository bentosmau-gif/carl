#ifndef CARL_NET_TCP_H
#define CARL_NET_TCP_H

#include <stdint.h>

void c_tcp_init(void);

int c_tcp_connect(
    uint32_t ip,
    uint16_t port
);

int c_tcp_send(
    void* data,
    uint32_t size
);

#endif /* CARL_NET_TCP_H */
