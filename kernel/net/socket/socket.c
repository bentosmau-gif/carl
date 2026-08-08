#include <stddef.h>
#include <stdint.h>

#include <carl/net/ipv4.h>
#include <carl/net/socket.h>

#define SOCKET_TABLE_SIZE 16U

typedef struct {
    int in_use;
    int type;
    uint32_t remote_ip;
    uint16_t remote_port;
} socket_state_t;

static socket_state_t g_sockets[SOCKET_TABLE_SIZE];

static int c_socket_find_free_slot(void) {
    for (uint32_t i = 0; i < SOCKET_TABLE_SIZE; ++i) {
        if (!g_sockets[i].in_use) {
            return (int)i;
        }
    }

    return -1;
}

c_socket c_create_socket(int type) {
    const int slot = c_socket_find_free_slot();

    if (slot < 0) {
        return -1;
    }

    g_sockets[slot].in_use = 1;
    g_sockets[slot].type = type;
    g_sockets[slot].remote_ip = 0U;
    g_sockets[slot].remote_port = 0U;

    return slot;
}

int c_socket_connect(c_socket sock, uint32_t ip, uint16_t port) {
    if (sock < 0 || (uint32_t)sock >= SOCKET_TABLE_SIZE) {
        return -1;
    }

    if (!g_sockets[sock].in_use) {
        return -1;
    }

    g_sockets[sock].remote_ip = ip;
    g_sockets[sock].remote_port = port;
    return 0;
}

int c_socket_send(c_socket sock, void *data, uint32_t size) {
    if (sock < 0 || (uint32_t)sock >= SOCKET_TABLE_SIZE) {
        return -1;
    }

    if (!g_sockets[sock].in_use || data == NULL) {
        return -1;
    }

    return c_IPv4Send(g_sockets[sock].remote_ip, data, size);
}

int c_socket_receive(c_socket sock, void *buffer, uint32_t size) {
    (void)sock;
    (void)buffer;
    (void)size;
    return 0;
}

int c_socket_close(c_socket sock) {
    if (sock < 0 || (uint32_t)sock >= SOCKET_TABLE_SIZE) {
        return -1;
    }

    g_sockets[sock].in_use = 0;
    g_sockets[sock].type = 0;
    g_sockets[sock].remote_ip = 0U;
    g_sockets[sock].remote_port = 0U;
    return 0;
}
