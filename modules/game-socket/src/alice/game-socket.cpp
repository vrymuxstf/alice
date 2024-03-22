#include <iostream>

#include "alice/game-socket.h"

namespace alice {
    GameSocket::GameSocket(asio::io_context &io, short port) : io_(io), socket_(io, udp::endpoint(udp::v4(), port)) {
        auto endpoint = socket_.local_endpoint();
        std::cout << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;
        Receive();
    }
}