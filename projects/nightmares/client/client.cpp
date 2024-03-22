#include <iostream>
#include <thread>

#include "alice/game-socket.h"

int main() {
    asio::io_context io;
    alice::GameSocket game_socket(io, 7777);
    std::thread thread([&io]() { io.run(); });

    std::cout << std::this_thread::get_id() << std::endl;

    while (true) {

    }

    io.stop();
    thread.join();
}