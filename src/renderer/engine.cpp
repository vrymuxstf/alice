#include "engine.h"
#include "singleton.h"

namespace alice {
#ifdef OPENGL
    Engine::Engine() : renderer_((GLADloadproc) Singleton<Platform>().GetContext()) {

    }
#elif VULKAN

    Engine::Engine() {

    }

#endif

    void Engine::Update() {
        auto time = Singleton<Platform>().GetTime();
        DeltaTime = time - last_time_;
        last_time_ = time;

        Singleton<Platform>().Update();
        renderer_.Update();

        if (Singleton<Platform>().ShouldClose()) {
            Running = false;
        }
    }
}