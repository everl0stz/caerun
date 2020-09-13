#pragma once

namespace net {
class AsyncSocket;
using RecvCallback_t = bool(*)(unsigned char* buf, AsyncSocket* sock);

class AsyncSocket {
public:
	virtual bool connect(const char* ip, unsigned short port, RecvCallback_t recv_callback) = 0;
	virtual void disconnect() = 0;

	virtual bool send(const void* data, size_t size) = 0;
};
}