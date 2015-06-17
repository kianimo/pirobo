#include "matstreamer.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void MatStreamer::sendMat(cv::Mat mat)
{
	mat = (mat.reshape(0,1));
	int  imgSize = mat.total()*mat.elemSize();

	int bytes_written = write(client_socket, mat.data, imgSize);
	if(bytes_written < 0)
		std::cout << "Fehler in sendMat()" << std::endl;
}

void MatStreamer::initialize_connection(const std::string &ip_addr, int port)
{
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Daten des Kommunikationsendpunktes initialiseren
	struct sockaddr_in to_addr;
	memset(&to_addr, 0, sizeof(to_addr));
	to_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip_addr.c_str(), &(to_addr.sin_addr));
	to_addr.sin_port = htons(port);

	int i = connect(client_socket, (struct sockaddr *) &to_addr, sizeof(to_addr));
	std::cout << i;
}

