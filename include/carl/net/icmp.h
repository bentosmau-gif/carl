#ifndef CARL_NET_ICMP_H
#define CARL_NET_ICMP_H

#include <stdint.h>

void c_ICMPInit(void);

int c_Ping(
    uint32_t destination
);

#endif /* CARL_NET_ICMP_H */
