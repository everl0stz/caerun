#pragma once
#include <nsock/nsock.h>

#include "udp_reliable.h"
#include "tcp_async.h"

namespace net {
class NetSystem {
private:
	UdpReliable udp_sock_;
	TcpAsync tcp_sock_;
public:
	bool connect(const char* ip, unsigned short port);
	void disconnect();
};
}