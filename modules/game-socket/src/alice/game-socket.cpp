#include "alice/game-socket.h"

namespace alice {
    GameSocket::GameSocket(asio::io_context &io, short port) : socket_(io, udp::endpoint(udp::v4(), port)) {
        Receive();
    }
}