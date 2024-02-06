#include "engine.h"

#include "camera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "opengl/imgui_impl_opengl3.h"

#include <glad/glad.h>

#include "render_objects/triangle_render_object.h"
#include "render_objects/mesh_render_object.h"
#include "render_objects/skybox_render_object.h"

#include "mesh_reader.h"

namespace alice {
    Engine::Engine() {
        glfwInit();

#ifdef VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

        window_ = glfwCreateWindow(1280, 720, "Alice", nullptr, nullptr);
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

        render_object_list_.Create<SkyboxRenderObject>();

        glfwGetCursorPos(window_, &last_cursor_pos_x, &last_cursor_pos_y);
    }

    void Engine::Update() {
        glfwPollEvents();

        auto time = glfwGetTime();
        DeltaTime = time - last_time_;
        last_time_ = time;

        double cursor_pos_x, cursor_pos_y;
        glfwGetCursorPos(window_, &cursor_pos_x, &cursor_pos_y);

        auto cursor_pos_x_offset = cursor_pos_x - last_cursor_pos_x;
        auto cursor_pos_y_offset = cursor_pos_y - last_cursor_pos_y;

        last_cursor_pos_x = cursor_pos_x;
        last_cursor_pos_y = cursor_pos_y;

        ImGui_ImplGlfw_NewFrame();

        ImGui_ImplOpenGL3_NewFrame();

        ImGui::NewFrame();

        ImGui::Begin("Hello, world!");
        ImGui::End();

        ImGui::Render();

        int width, height;
        glfwGetFramebufferSize(window_, &width, &height);

        if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            Camera::Singleton().rotation.x += (float) (DeltaTime * -cursor_pos_y_offset * 100);
            Camera::Singleton().rotation.y += (float) (DeltaTime * cursor_pos_x_offset * 100);

            std::cout << Camera::Singleton().rotation.x << std::endl;
        }

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