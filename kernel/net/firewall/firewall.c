#include <stdint.h>

#include <carl/net/firewall.h>

static uint32_t g_blocked_ranges[4U] = {
    0xC0A80000U,
    0x00000000U,
    0x00000000U,
    0x00000000U
};

c_firewall_action c_firewall_check(
    uint32_t source,
    uint32_t destination
) {
    (void)destination;

    for (uint32_t i = 0; i < 4U; ++i) {
        if (g_blocked_ranges[i] == 0U) {
            continue;
        }

        if (source == g_blocked_ranges[i]) {
            return CARL_FIREWALL_DENY;
        }
    }

    return CARL_FIREWALL_ALLOW;
}
