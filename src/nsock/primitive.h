#pragma once
#include <optional>
#include <stdint.h>

#include "defs.h"

namespace nsock {
class Socket {
public:
	Socket() = default;
	// Disconnects from server if obiect is out of scope
	virtual ~Socket() { };

	virtual ConnectResult_t connect(const char* ip, unsigned short port) = 0;
	// Similar to RD / WR / RDWR
	virtual bool disconnect(DisconnectMode_t how) = 0;

	// -1 indicates error, otherwise returns number of bytes sent
	virtual int send(const void* data, size_t size) = 0;
	// Returns false if errors ocurred somewhere in sending process
	virtual bool sendAll(const void* data, size_t size) = 0;
	// -1 indicates error, otherwise returns number of bytes read
	virtual int recv(void* buf, size_t size) = 0;
	// -1 indicates error, -2 no data to read, otherwise returns number of bytes read
	virtual int recvNonblocking(void* buf, size_t size) = 0;
};
}