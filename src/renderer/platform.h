#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

namespace alice {
    class Platform {
        bool initialized_ = false;
        GLFWwindow *window;
    public:
        Platform();

        ~Platform();

        void Update();

        [[nodiscard]] double GetTime() const;

        [[nodiscard]] GLFWglproc GetContext() const;

        [[nodiscard]] bool ShouldClose() const;
    };
}