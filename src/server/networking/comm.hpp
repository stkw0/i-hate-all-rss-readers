#pragma once

#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Comm  {
public:
	void listen(const std::string& bind, unsigned port);
	std::string readPacket();
	void writePacket(std::string& p);
private: // Methods
private: // Data
	boost::asio::io_context io_context;
	 tcp::socket socket{io_context};
};