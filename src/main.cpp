#include <iostream>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " <server> <nickname> \n";
		return 1;
	}

	const char* server_ip = argv[1];
	const char* nickname = argv[2];

	std::cout << "Remote server\'s IP: " << server_ip << "\n";
	std::cout << "Your nickname: " << nickname << "\n";

	return 0;
}
