#include "net_system.h"
#include <cstring>
#include <cstdio>

namespace net {
bool NetSystem::connect(const char* ip, unsigned short port) {
	if (!tcp_sock_.connect(ip, port, [](unsigned char* buf, AsyncSocket* sock) -> bool { return true; })) return false;
	if (!udp_sock_.connect(ip, port, [](unsigned char* buf, AsyncSocket* sock) -> bool { return true; })) return false;

	tcp_sock_.send(ip, strlen(ip));
	udp_sock_.send(ip, strlen(ip));

	return true;
}
}
