#pragma once
#include <netinet/in.h>

#include "primitive.h"

namespace nsock {
class UdpClient : public Socket {
private:
	int fd_{ -1 };
	sockaddr_in dst_{};
public:
	UdpClient() = default;
	~UdpClient();

	ConnectResult_t connect(const char* ip, unsigned short port) override;
	bool disconnect(DisconnectMode_t how = DisconnectMode_t::ALL) override;

	int send(const void* data, size_t size) override;
	bool sendAll(const void* data, size_t size) override;
	// sendAll-like
	bool sendTo(const void* data, size_t size, const char* ip, unsigned short port);
	int recv(void* buf, size_t size) override;
	int recvNonblocking(void* buf, size_t size) override;
};
}