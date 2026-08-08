#include <stdint.h>

#include <carl/net/route.h>

static uint32_t g_default_gateway = 0xC0A80001U; /* 192.168.0.1 */

void c_routeInit(void) {
    g_default_gateway = 0xC0A80001U;
}

uint32_t c_routeGetGateway(uint32_t destination) {
    (void)destination;
    return g_default_gateway;
}
