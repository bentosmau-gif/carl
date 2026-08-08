#include <stddef.h>
#include <stdint.h>

#include <carl/net/ipv4.h>
#include <carl/net/udp.h>

void c_udp_init(void) {
    /* UDP initialized as a lightweight stub for the current kernel. */
}

int c_udp_send(
    uint32_t ip,
    uint16_t port,
    void *data,
    uint32_t size
) {
    (void)port;

    if (data == NULL || size == 0U) {
        return -1;
    }

    return c_IPv4Send(ip, data, size);
}
