#ifdef __unix__
#include <cerrno>
#include <netdb.h>
#include <optional>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "tcp_unix.h"

namespace nsock {
TcpClient::~TcpClient() {
	if (fd_ != -1)
		disconnect();
}

ConnectResult_t TcpClient::connect(const char* ip, unsigned short port) {
	sockaddr_in saddr{};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);

	hostent* he = gethostbyname(ip);
	if (he == nullptr) return ConnectResult_t::ERR_GETHOSTBYNAME;

	fd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_ == -1) return ConnectResult_t::ERR_SOCKET;

	if (::connect(fd_, reinterpret_cast<sockaddr*>(&saddr), sizeof(saddr)) == -1)
	return ConnectResult_t::ERR_CONNECT;

	return ConnectResult_t::OK;
}

bool TcpClient::disconnect(DisconnectMode_t how) {
	if (how == DisconnectMode_t::READ) {
		return shutdown(fd_, SHUT_RD) != -1;
	}
	else if (how == DisconnectMode_t::WRITE) {
		return shutdown(fd_, SHUT_WR) != -1;
	}
	else if (how == DisconnectMode_t::ALL) {
		auto ret = shutdown(fd_, SHUT_RDWR) != -1;
		close(fd_);
		fd_ = -1;
		return ret;
	}

	return false;
}

int TcpClient::send(const void* data, size_t size) {
	return ::send(fd_, data, size, 0);
}

bool TcpClient::sendAll(const void* data, size_t size) {
	size_t sent = 0;
	while (sent < size) {
		auto ret = this->send(data, size);
		if (ret == -1) return false;
		sent += ret;
	}
	
	return true;
}

int TcpClient::recv(void* buf, size_t size) {
	return ::recv(fd_, buf, size, 0);
}

int TcpClient::recvNonblocking(void* buf, size_t size) {
	auto ret = ::recv(fd_, buf, size, MSG_DONTWAIT);
	if (ret == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
		return -2;

	return ret;
}
}
#endif