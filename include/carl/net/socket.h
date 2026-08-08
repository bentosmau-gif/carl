#ifndef CARL_NET_SOCKET_H
#define CARL_NET_SOCKET_H

#include <stdint.h>

typedef int c_socket;

c_socket c_create_socket(int type);

int c_socket_connect(c_socket sock, uint32_t ip, uint16_t port);

int c_socket_send(c_socket sock, void* data, uint32_t size);

int c_socket_receive(c_socket sock, void* buffer, uint32_t size);

int c_socket_close(c_socket sock);

#endif /* CARL_NET_SOCKET_H */

