#include "platform.h"

namespace alice {
    Platform::Platform() {
        glfwInit();

#if VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

        window = glfwCreateWindow(1280, 720, "", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        initialized_ = true;
    }

    Platform::~Platform() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    double Platform::GetTime() const {
        if (initialized_) return glfwGetTime();
        return 0;
    }

    GLFWglproc Platform::GetContext() const {
        if (initialized_) return (GLFWglproc) glfwGetProcAddress;
        return nullptr;
    }

    void Platform::Update() {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    bool Platform::ShouldClose() const {
        return glfwWindowShouldClose(window);
    }
}