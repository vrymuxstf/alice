#include "engine.h"

#include "camera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "opengl/imgui_impl_opengl3.h"

#include <glad/glad.h>

#include "render_objects/triangle_render_object.h"
#include "render_objects/mesh_render_object.h"

#include "mesh_reader.h"

namespace alice {
    Engine::Engine() {
        glfwInit();

#ifdef VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

        window_ = glfwCreateWindow(1280, 720, "", nullptr, nullptr);
        glfwMakeContextCurrent(window_);

#ifdef OPENGL
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
#endif

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

#ifdef OPENGL
        ImGui_ImplGlfw_InitForOpenGL(window_, true);
        ImGui_ImplOpenGL3_Init();
#endif

        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };

        render_object_list_.Create<TriangleRenderObject>(vertices, sizeof(vertices));

        MeshReader reader;
        reader.Read("mesh.fbx");

        render_object_list_.Create<MeshRenderObject>(reader.vertices, reader.indices);
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

        int width, height;
        glfwGetFramebufferSize(window_, &width, &height);

        Camera::Singleton().width = width;
        Camera::Singleton().height = height;

#ifdef OPENGL
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0, 0.5f, 1.0f);
#endif

        for (auto *renderer_object: render_object_list_) {
            renderer_object->Draw();
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

#ifdef OPENGL
        glfwSwapBuffers(window_);
#endif

        if (glfwWindowShouldClose(window_)) {
            Running = false;
        }
    }

    Engine::~Engine() {
        glfwTerminate();
    }
}