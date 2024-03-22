#include <iostream>

#include "asio.hpp"

using asio::ip::udp;

namespace alice {
    class GameSocket {
        udp::socket socket_;
        udp::endpoint remote_endpoint_;
        std::array<char, 1024> buffer_{};

        void Receive() {
            socket_.async_receive_from(
                    asio::buffer(buffer_),
                    remote_endpoint_,
                    [this](asio::error_code ec, std::size_t bytes) {
                        if (!ec && bytes > 0) {
                            std::string message(buffer_.data(), bytes);
                            std::cout << "Received: " << message << std::endl;
                        }
                        Receive();
                    }
            );
        }

    public:
        explicit GameSocket(asio::io_context &io, short port = 0);
    };
}