#include <stddef.h>
#include <stdint.h>

#include <carl/net/icmp.h>
#include <carl/net/ipv4.h>

void c_ICMPInit(void) {
    /* ICMP stub is prepared for future expansion. */
}

int c_Ping(uint32_t destination) {
    static const char ping_payload[] = "PING";

    return c_IPv4Send(destination, (void *)ping_payload, 4U);
}
