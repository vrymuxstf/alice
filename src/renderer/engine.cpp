#include "engine.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"

#include <glad/glad.h>

namespace alice {
    Engine::Engine() {
        glfwInit();

#if VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

        window = glfwCreateWindow(1280, 720, "", nullptr, nullptr);
        glfwMakeContextCurrent(window);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
    }

    void Engine::Update() {
        glfwPollEvents();

        auto time = glfwGetTime();
        DeltaTime = time - last_time_;
        last_time_ = time;

#ifdef OPENGL
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0, 0.5f, 1.0f);
#endif
        for (auto *renderer_object: render_object_list_) {
            renderer_object->Draw();
        }

        glfwSwapBuffers(window);

        if (glfwWindowShouldClose(window)) {
            Running = false;
        }
    }

    Engine::~Engine() {
        glfwTerminate();
    }
}