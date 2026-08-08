#include <stddef.h>
#include <stdint.h>

#include <carl/net/ipv4.h>
#include <carl/net/tcp.h>

static uint32_t g_tcp_peer_ip = 0U;
static uint16_t g_tcp_peer_port = 0U;
static int g_tcp_connected = 0;

void c_tcp_init(void) {
    g_tcp_peer_ip = 0U;
    g_tcp_peer_port = 0U;
    g_tcp_connected = 0;
}

int c_tcp_connect(
    uint32_t ip,
    uint16_t port
) {
    g_tcp_peer_ip = ip;
    g_tcp_peer_port = port;
    g_tcp_connected = 1;
    return 0;
}

int c_tcp_send(
    void *data,
    uint32_t size
) {
    if (data == NULL || size == 0U || !g_tcp_connected) {
        return -1;
    }

    return c_IPv4Send(g_tcp_peer_ip, data, size);
}
