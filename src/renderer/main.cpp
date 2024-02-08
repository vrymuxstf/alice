#include "engine.h"

int main() {
    while (alice::Engine::Singleton().Running) {
        alice::Engine::Singleton().Update();
    }
    return 0;
}