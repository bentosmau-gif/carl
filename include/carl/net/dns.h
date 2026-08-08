#ifndef CARL_NET_DNS_H
#define CARL_NET_DNS_H

#include <stdint.h>

void c_dnsInit(void);

int c_dnsResolve(
    const char* hostname,
    uint32_t* ip
);

#endif /* CARL_NET_DNS_H */
