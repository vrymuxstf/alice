#include "engine.h"
#include "singleton.h"

int main() {
    while (alice::Singleton<alice::Engine>().Running) {
        alice::Singleton<alice::Engine>().Update();
    }
    return 0;
}