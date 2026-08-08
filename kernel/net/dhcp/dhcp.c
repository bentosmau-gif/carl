#include <stddef.h>
#include <stdint.h>

#include <carl/net/dhcp.h>

void c_dhcpInit(void) {
    /* DHCP state is intentionally minimal for the current kernel stub. */
}

int c_dhcpRequestIp(
    uint32_t *ip,
    uint32_t *gateway,
    uint32_t *dns
) {
    if (ip != NULL) {
        *ip = 0xC0A8000AU; /* 192.168.0.10 */
    }

    if (gateway != NULL) {
        *gateway = 0xC0A80001U; /* 192.168.0.1 */
    }

    if (dns != NULL) {
        *dns = 0x08080808U; /* 8.8.8.8 */
    }

    return 0;
}
