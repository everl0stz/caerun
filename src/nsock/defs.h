#pragma once

namespace nsock {
constexpr auto BUF_SIZE = 1024;

enum class ConnectResult_t {
	OK,
	ERR_GETHOSTBYNAME,
	ERR_CONNECT,
	ERR_SOCKET
};

enum class DisconnectMode_t {
	READ, WRITE, ALL
};

enum SendResult_t {
	SR_OK
};

enum RecvResult_t {
	RR_OK
};
}