#include <iostream>

#include "asio.hpp"

using asio::ip::udp;

namespace alice {
    class GameSocket {
        asio::io_context &io_;
        udp::socket socket_;
        udp::endpoint remote_endpoint_;
        std::array<char, 1024> buffer_{};
        std::string message_;

        virtual void OnMessage(const std::string &content) {
            std::cout << "Thread:[" << std::this_thread::get_id() << "] : " << content << std::endl;
        }

        void Receive() {
            socket_.async_receive_from(
                    asio::buffer(buffer_),
                    remote_endpoint_,
                    [this](asio::error_code ec, std::size_t bytes) {
                        if (!ec && bytes > 0) {

                            message_ = std::string(buffer_.data(), bytes);

                            asio::post(io_, [this]() { OnMessage(message_); });
                        }
                        Receive();
                    }
            );
        }

    public:
        explicit GameSocket(asio::io_context &io, short port = 0);
    };
}