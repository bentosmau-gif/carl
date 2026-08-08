#ifndef CARL_NET_FIREWALL_H
#define CARL_NET_FIREWALL_H

#include <stdint.h>

typedef enum {
    CARL_FIREWALL_ALLOW,
    CARL_FIREWALL_DENY
} c_firewall_action;

c_firewall_action 
c_firewall_check
(uint32_t source, 
uint32_t destination);

#endif /* CARL_NET_FIREWALL_H */
