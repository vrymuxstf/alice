#include "engine.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "opengl/imgui_impl_opengl3.h"

#include <glad/glad.h>

#include "triangle_render_object.h"

namespace alice {
    Engine::Engine() {
        glfwInit();

#if VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

        window_ = glfwCreateWindow(1280, 720, "", nullptr, nullptr);
        glfwMakeContextCurrent(window_);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window_, true);
        ImGui_ImplOpenGL3_Init();

        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };

        render_object_list_.Create<TriangleRenderObject>(vertices, sizeof(vertices));
    }

    void Engine::Update() {
        glfwPollEvents();

        auto time = glfwGetTime();
        DeltaTime = time - last_time_;
        last_time_ = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hello, world!");
        ImGui::End();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window_, &display_w, &display_h);

#ifdef OPENGL
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0, 0.5f, 1.0f);
#endif

        for (auto *renderer_object: render_object_list_) {
            renderer_object->Draw();
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);

        if (glfwWindowShouldClose(window_)) {
            Running = false;
        }
    }

    Engine::~Engine() {
        glfwTerminate();
    }
}