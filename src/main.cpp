#include <iostream>
#include "sensors/vision.hpp"
#include "actors/DirectionMovement.h"
#include "server/server.h"

int main(int argc, char* argv[]) {
	DirectionMovement mov;

	int port = 4242;
	if(argc >= 2) {
		port = atoi(argv[1]);
		if((port > 65535) || (port < 2000)) {
			std::cerr << "Port number must be between 2000 - 65535." << std::endl;
			return EXIT_FAILURE;
		}
	}

	Server m_server(port);

	while(true){
		m_server.start();
		std::cout << "Connection established." << std::endl;
		bool finish = false;
		while(!finish){
			std::string command;
			std::string answer;
			try{
				command = m_server.receive_string();
				std::cout << command << std::endl;
				answer = mov.getCommand(command);
				std::cout << answer << std::endl;
				m_server.send_string(answer);
			} catch (std::exception ex){
				break;
			}
		}
		std::cout << "Connection closed." << std::endl;
	}

	return EXIT_SUCCESS;
}
