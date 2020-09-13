#pragma once
#include <nsock/nsock.h>

#include "async_socket.h"

namespace net {
class TcpAsync : public AsyncSocket {
private:
	nsock::TcpClient client_;
	RecvCallback_t recv_callback_;
public:
	bool connect(const char* ip, unsigned short port, RecvCallback_t recv_callback);
	void disconnect();

	bool send(const void* data, size_t size);
};
}