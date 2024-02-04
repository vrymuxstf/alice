#pragma once

#include "singleton.h"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include "object_list.h"
#include "render_object.h"

namespace alice {
    class Engine {
        GLFWwindow *window;
        ObjectList<RenderObject> render_object_list_;
        double last_time_ = 0;
    public:
        Engine();

        ~Engine();

        bool Running = true;
        double DeltaTime = 0;

        void Update();
    };
}