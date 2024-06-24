#pragma once

namespace alice::core {
    class App {
    public:
        bool running = true;

        static App &GetSingleton() {
            static App app;
            return app;
        }
    };
}
