/*
* Server.h
*/

#ifndef SERVER_H
#define SERVER_H

class Server {
public:
	Server(int port);
	void start();
	void send_string(std::string str);
	std::string receive_string();
};

#endif
