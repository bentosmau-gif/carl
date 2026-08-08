#ifndef CARL_NET_WIFI_H
#define CARL_NET_WIFI_H

#include <stdint.h>

typedef struct {
    char ssid[32];          // SSID (Service Set Identifier)
    uint8_t signal_strength;  // Signal Strength (0-100)
    uint8_t connected;          // Connection Status (0 = Disconnected, 1 = Connected)
} wifi_header_t;

void c_WiFiInit(void);

int c_WiFiConnect(
    const char *ssid,
    const char *password
);

int c_WiFiDisconnect(void);

#endif /* CARL_NET_WIFI_H */
