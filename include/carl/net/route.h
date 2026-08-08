#ifndef CARL_NET_ROUTE_H
#define CARL_NET_ROUTE_H

#include <stdint.h>

void c_routeInit(void);

uint32_t c_routeGetGateway(uint32_t destination);

#endif /* CARL_NET_ROUTE_H */
