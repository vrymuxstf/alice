#pragma once

namespace alice::core {
    class App;

    class Subsystem {
    public:
        explicit Subsystem(App *app) {
        }

        virtual ~Subsystem() = default;

        virtual void Update() = 0;
    };
}
