/*
 * MatStreamer.hpp
 *
 *  Created on: 16.06.2015
 *      Author: imma
 */

#ifndef PIROBO_SRC_SENSORS_MATSTREAMER_HPP_
#define PIROBO_SRC_SENSORS_MATSTREAMER_HPP_

#include <string>
#include <sys/socket.h>
#include <opencv/cv.h>

class MatStreamer
{
	public:
		MatStreamer(const std::string &ip_address, int port)
		{
			initialize_connection(ip_address, port);
		}

		void sendMat(cv::Mat mat);

	private:
		void initialize_connection(const std::string &ip_addr, int port);
		int client_socket;

};

#endif /* PIROBO_SRC_SENSORS_MATSTREAMER_HPP_ */
