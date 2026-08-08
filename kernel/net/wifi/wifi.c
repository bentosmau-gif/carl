#include <stddef.h>
#include <stdint.h>

#include <carl/net/wifi.h>

static wifi_header_t g_wifi_state = {
    .ssid = "carl-net",
    .signal_strength = 75U,
    .connected = 0U
};

void c_WiFiInit(void) {
    g_wifi_state.signal_strength = 75U;
    g_wifi_state.connected = 0U;
}

int c_WiFiConnect(
    const char *ssid,
    const char *password
) {
    (void)password;

    if (ssid == NULL) {
        return -1;
    }

    for (uint32_t i = 0; i < 31U; ++i) {
        g_wifi_state.ssid[i] = ssid[i];
        if (ssid[i] == '\0') {
            break;
        }
    }

    g_wifi_state.ssid[31] = '\0';
    g_wifi_state.connected = 1U;
    g_wifi_state.signal_strength = 90U;
    return 0;
}

int c_WiFiDisconnect(void) {
    g_wifi_state.connected = 0U;
    g_wifi_state.signal_strength = 0U;
    return 0;
}
