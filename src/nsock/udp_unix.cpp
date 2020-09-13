#ifdef __unix__
#include <cerrno>
#include <netdb.h>
#include <optional>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "udp_unix.h"
#endif

namespace nsock {
UdpClient::~UdpClient() {
	if (fd_ != -1)
		disconnect();
}

ConnectResult_t UdpClient::connect(const char* ip, unsigned short port) {
	fd_ = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd_ == -1) return ConnectResult_t::ERR_SOCKET;

	dst_.sin_family = AF_INET;
	dst_.sin_port = htons(port);
	dst_.sin_addr.s_addr = INADDR_ANY;

	return ConnectResult_t::OK;
}

bool UdpClient::disconnect(DisconnectMode_t how) {
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

int UdpClient::send(const void* data, size_t size) {
	return ::sendto(fd_, data, size, 0, reinterpret_cast<sockaddr*>(&dst_), sizeof(dst_));
}

bool UdpClient::sendAll(const void* data, size_t size) {
	size_t sent = 0;
	while (sent < size) {
		auto ret = this->send(data, size);
		if (ret == -1) return false;
		sent += ret;
	}
	
	return true;
}

bool UdpClient::sendTo(const void* data, size_t size, const char* ip, unsigned short port) {
	sockaddr_in dst{};
	dst.sin_family = AF_INET;
	dst.sin_port = htons(port);
	dst.sin_addr.s_addr = INADDR_ANY;

	size_t sent = 0;
	while (sent < size) {
		auto ret = ::sendto(fd_, data, size, 0, reinterpret_cast<sockaddr*>(&dst), sizeof(dst));
		if (ret == -1) return false;
		sent += ret;
	}

	return true;
}

int UdpClient::recv(void* buf, size_t size) {
	return ::recv(fd_, buf, size, 0);
}

int UdpClient::recvNonblocking(void* buf, size_t size) {
	auto ret = ::recv(fd_, buf, size, MSG_DONTWAIT);
	if (ret == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
		return -2;

	return ret;
}
}