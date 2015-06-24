#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include "server.h"

int port, server_socket, client_socket; 
socklen_t sock_len;
struct sockaddr_in svrAdd, clntAdd;

Server::Server(int p){
	port = p;

	//create socket
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket < 0) { 
		std::cerr << "Cannot open socket." << std::endl; // << strerror(errno) << std::endl;
		throw std::exception();
	}

	bzero(&svrAdd, sizeof(svrAdd));
	svrAdd.sin_family = AF_INET;
	svrAdd.sin_addr.s_addr = INADDR_ANY;
	svrAdd.sin_port = htons(port);

	//bind socket
	if(bind(server_socket, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0){
		std::cerr << "Cannot bind." << std::endl; // << strerror(errno) << std::endl;
		throw std::exception();
	}

	if(listen(server_socket, 5) < 0){
		std::cerr << "Cannot listen on server socket." << std::endl; //<< strerror(errno) << std::endl;
		throw std::exception();
	}
}

void Server::start(){
	std::cout << "listening on port " << port << "." << std::endl;
	client_socket = accept(server_socket, (struct sockaddr *)&clntAdd, &sock_len);	
	if(client_socket < 0){
		std::cerr << "Cannot accept connection." << std::endl; // << strerror(errno) << std::endl;
		throw std::exception();
	}
}

void Server::send_string(std::string str){
	if(!send(client_socket, str.c_str(), str.size(), 0)){
		std::cout << "Failed to send data to client." << std::endl;
	}	
}

std::string Server::receive_string(){
	char buffer[256];
	bzero(buffer, 256);
	int n = read(client_socket, buffer, 255);
	if(n <= 0){ 
		std::cerr << "ERROR reading from socket." << std::endl;
		close(client_socket);
		throw std::exception();
	}
	std::string str = buffer;
	str.erase(str.find_last_not_of(" \n\r\t")+1);
	return str;
}
