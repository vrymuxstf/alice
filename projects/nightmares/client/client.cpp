#include <iostream>
#include <thread>

#include "alice/game-socket.h"

int main() {
    bool running = true;

    alice::GameSocket game_socket(7777);

    std::thread thread([&running]() {
        while (running) {
            std::string input;
            std::getline(std::cin, input);
            if (input == "exit") {
                running = false;
            }
        }
    });

    while (running) {
        game_socket.Update();
    }

    thread.join();

    game_socket.Shutdown();

    return 0;
}