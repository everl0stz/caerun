#pragma once
#include "primitive.h"

namespace nsock {
class TcpClient : public Socket {
private:
	int fd_{ -1 };
public:
	TcpClient() = default;
	~TcpClient();

	ConnectResult_t connect(const char* ip, unsigned short port) override;
	bool disconnect(DisconnectMode_t how = DisconnectMode_t::ALL) override;

	int send(const void* data, size_t size) override;
	bool sendAll(const void* data, size_t size) override;
	int recv(void* buf, size_t size) override;
	int recvNonblocking(void* buf, size_t size) override;
};
}