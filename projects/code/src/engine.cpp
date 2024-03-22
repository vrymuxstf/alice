#include "engine.h"

#include "camera.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/glad.h>

#include "render_objects/triangle_render_object.h"
#include "render_objects/skybox_render_object.h"
#include "render_objects/editor_grids_render_object.h"

#include "entities/mesh.h"

namespace alice {
    Entity *g_Scene = nullptr;

    void UpdateEntity(Entity *entity, float delta_time) {
        entity->Update(delta_time);
        for (const auto &dep: entity->GetDependencies()) {
            UpdateEntity(dep, delta_time);
        }
    }

    void RenderEntityImGui(Entity *entity) {
        auto opened = ImGui::TreeNode((entity), "%s", entity->GetName().c_str());

        if (opened) {
            if (ImGui::Button("Add Entity")) {
                ImGui::OpenPopup("Add Entity");
            }

            if (entity->GetOwner()) {
                if (ImGui::Button("Deleted")) {
                    entity->GetOwner()->DeleteDependency(entity);
                }
            }

            if (entity) {
                if (ImGui::BeginPopup("Add Entity")) {

                    if (ImGui::Button("Mesh")) {
                        entity->CreateDependency<Mesh>();
                        ImGui::CloseCurrentPopup();
                    }

                    if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_NoPopupHierarchy)) {
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();
                }

                entity->DisplayImGui();

                for (const auto &dep: entity->GetDependencies()) {
                    RenderEntityImGui(dep);
                }
            }

            ImGui::TreePop();
        }
    }

    Engine::Engine() {
        EntityProperties properties;
        g_Scene = new Entity;

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

        window_ = glfwCreateWindow(1280, 720, "Alice", nullptr, nullptr);


        glfwMakeContextCurrent(window_);

#ifdef OPENGL
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

/*        {
            float vertices[] = {
                    -0.75f, -0.75f, 0.9f, 1.0f, 1.0f, 1.0f, 1.0f,
                    0.75f, -0.75f, 0.9f, 1.0f, 1.0f, 1.0f, 1.0f,
                    0.0f, 0.75f, 0.9f, 1.0f, 1.0f, 1.0f, 1.0f
            };

            render_object_list_.Create<TriangleRenderObject>(vertices, sizeof(vertices));
        }

        {
            float vertices[] = {
                    -0.75f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                    0.25f, -0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f,
                    0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f
            };

            render_object_list_.Create<TriangleRenderObject>(vertices, sizeof(vertices));
        }

        {
            float vertices[] = {
                    -0.625f, -0.625f, 0.75f, 0.0f, 0.0f, 0.0f, 1.0f,
                    0.625f, -0.625f, 0.75f, 0.0f, 0.0f, 0.0f, 1.0f,
                    0.0f, 0.625f, 0.75f, 0.0f, 0.0f, 0.0f, 1.0f
            };

            render_object_list_.Create<TriangleRenderObject>(vertices, sizeof(vertices));
        }*/

        render_object_list_.Create<SkyboxRenderObject>();
        render_object_list_.Create<EditorGridsRenderObject>();

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

        UpdateEntity(g_Scene, (float) DeltaTime);

        ImGui_ImplGlfw_NewFrame();

        ImGui_ImplOpenGL3_NewFrame();

        ImGui::NewFrame();

        ImGui::BeginMainMenuBar();
        ImGui::MenuItem("Tree");
        ImGui::EndMainMenuBar();

        ImGui::Begin("Tree");
        RenderEntityImGui(g_Scene);
        ImGui::End();

        ImGui::Render();

        int width, height;
        glfwGetFramebufferSize(window_, &width, &height);

        if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            Camera::Singleton().rotation.x += (float) (DeltaTime * -cursor_pos_y_offset * 200);
            Camera::Singleton().rotation.y += (float) (DeltaTime * cursor_pos_x_offset * 200);

            if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
                Camera::Singleton().position += 5.0f * (float) (DeltaTime) * Camera::Singleton().GetForward();
            }

            if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
                Camera::Singleton().position -= 5.0f * (float) (DeltaTime) * Camera::Singleton().GetForward();
            }

            if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
                Camera::Singleton().position += 5.0f * (float) (DeltaTime) * Camera::Singleton().GetRight();
            }

            if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
                Camera::Singleton().position -= 5.0f * (float) (DeltaTime) * Camera::Singleton().GetRight();
            }

            if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS) {
                Camera::Singleton().position.y += 5.0f * (float) (DeltaTime);
            }

            if (glfwGetKey(window_, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
                Camera::Singleton().position.y -= 5.0f * (float) (DeltaTime);
            }

        } else {
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        Camera::Singleton().width = width;
        Camera::Singleton().height = height;

#ifdef OPENGL
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);
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
        delete g_Scene;
    }
}