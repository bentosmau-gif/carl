#ifndef CARL_NET_DHCP_H
#define CARL_NET_DHCP_H

#include <stdint.h>

void c_dhcpInit(void);

int c_dhcpRequestIp(
    uint32_t* ip,
    uint32_t* gateway,
    uint32_t* dns
);

#endif /* CARL_NET_DHCP_H */
