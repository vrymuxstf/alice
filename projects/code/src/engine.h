#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include "object_list.h"
#include "render_object.h"

#include "entity.h"

namespace alice {
    class Engine {
        GLFWwindow *window_;
        ObjectList<RenderObject> render_object_list_;
        ObjectList<Entity> entities_;
        double last_time_ = 0;
        double last_cursor_pos_x = 0;
        double last_cursor_pos_y = 0;
    public:
        static Engine &Singleton() {
            static Engine instance;
            return instance;
        }

        Engine();

        ~Engine();

        bool Running = true;
        double DeltaTime = 0;

        void Update();

        [[nodiscard]] ObjectList<RenderObject> &GetRenderObjectList() { return render_object_list_; }
    };
}