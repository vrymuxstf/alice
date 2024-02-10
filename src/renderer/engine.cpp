#include "engine.h"

#include "camera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "opengl/imgui_impl_opengl3.h"

#include <glad/glad.h>

#include "render_objects/triangle_render_object.h"
#include "render_objects/skybox_render_object.h"

#include "component_factory.h"

namespace alice {
    Engine::Engine() {
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

        ImGui::BeginMainMenuBar();
        ImGui::MenuItem("Tree");
        ImGui::EndMainMenuBar();

        ImGui::Begin("Tree");
        if (ImGui::Button("Create Entity")) {
            entities_.Create<Entity>();
        }

        for (const auto &entity: entities_.Get()) {
            auto topped = ImGui::TreeNode((entity), "Entity");

            if (topped) {
                if (ImGui::Button("Delete")) {
                    entities_.Destroy(entity);
                }

                if (ImGui::Button("Add Component")) {
                    ImGui::OpenPopup("Components");
                }

                if (ImGui::BeginPopup("Components")) {
                    for (const auto &name: ComponentFactory::GetComponentNames()) {
                        if (ImGui::Button(name.c_str())) {
                            entity->CreateComponent(name);
                        }
                    }
                    ImGui::EndPopup();
                }

                for (const auto &component: entity->GetComponent()) {
                    component->Update((float) DeltaTime);

                    bool opened = ImGui::TreeNode(component, "%s", component->GetClassName().c_str());

                    if (opened) {
                        bool removed = false;
                        if (ImGui::Button("Delete")) {
                            entity->DestroyComponent(component);
                            removed = true;
                        }

                        if (!removed) {
                            component->DisplayImGui();
                        }
                        ImGui::TreePop();
                    }
                }
            }

            if (topped) {
                ImGui::TreePop();
            }
        }

        ImGui::End();

        ImGui::Render();

        int width, height;
        glfwGetFramebufferSize(window_, &width, &height);

        if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            Camera::Singleton().rotation.x += (float) (DeltaTime * -cursor_pos_y_offset * 100);
            Camera::Singleton().rotation.y += (float) (DeltaTime * cursor_pos_x_offset * 100);

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
    }
}