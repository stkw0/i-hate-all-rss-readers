#include <array>
#include <cctype>
#include <iostream>

#include <boost/array.hpp>

#include "comm.hpp"

void Comm::listen(const std::string& bind, unsigned port) {
    static tcp::acceptor acceptor{io_context, tcp::endpoint(tcp::v4(), port)};
    socket = tcp::socket(io_context);
    acceptor.accept(socket);
}

std::string Comm::readPacket() {
    std::array<char, 1024> buf;
    boost::system::error_code error;

    auto len = socket.read_some(boost::asio::buffer(buf), error);

    if(error) throw boost::system::system_error(error);

    std::string join;
    for(unsigned i = 0; i < len; i++) join += buf[i];

    return join;
}

void Comm::writePacket(std::string& p) {
    std::cout << p << std::endl;
    socket.send(boost::asio::buffer(p.c_str(), p.length()));
}
