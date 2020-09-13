#include <thread>
#include <cstring>

#include "udp_reliable.h"

namespace net {
bool UdpReliable::connect(const char* ip, unsigned short port, RecvCallback_t recv_callback) {
	recv_callback_ = recv_callback;
	const auto result = client_.connect(ip, port) == nsock::ConnectResult_t::OK;
	if (!result) return false;
	std::thread([this] {
		unsigned char buf[1024] = { '\0' };
		bool runs = true;
		while (runs) {
			client_.recv(buf, sizeof(buf));
			runs = recv_callback_(buf, this);
			memset(buf, 0, sizeof(buf));
		}
	}).detach();

	return true;
}

void UdpReliable::disconnect() {
	client_.disconnect();
}

bool UdpReliable::send(const void* data, size_t size) {
	return client_.sendAll(data, size) != -1;
}
}