#pragma once

#include "platform.h"
#include "renderer.h"

namespace alice {
    class Engine {
        double last_time_ = 0;
        Renderer renderer_;
    public:
        Engine();

        bool Running = true;
        double DeltaTime = 0;

        void Update();
    };
}