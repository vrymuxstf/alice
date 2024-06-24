#pragma once

#include <iostream>

#include "alice/core/app.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <alice/renderer/object_manager.h>
#include <alice/renderer/object_triangle.h>

#include "alice/game-framework/property_types.h"
#include "alice/game-framework/space_class_registrant.h"
#include "alice/game-framework/world.h"
#include "alice/renderer/framebuffer.h"

void DrawProperty(alice::game::framework::Property *property) {
    if (const auto property_string = dynamic_cast<alice::game::framework::PropertyString *>(property)) {
        ImGui::InputText(property->GetName().c_str(), property_string->GetValuePtr());
    }

    if (const auto property_vector = dynamic_cast<alice::game::framework::PropertyVector *>(property)) {
        ImGui::DragFloat3(property->GetName().c_str(), (float *) property_vector->GetValuePtr());
    }
}

void DrawEntity(const alice::game::framework::Space *space) {
    if (ImGui::TreeNode(space, "%s", "Space")) {
        for (const auto &prop: space->GetProperties()) {
            DrawProperty(prop);
        }

        if (ImGui::Button("See")) {
            for (const auto &prop: space->GetProperties()) {
                std::cout << prop->Out() << std::endl;
            }
        }

        ImGui::TreePop();
    }
}

int main() {
    alice::renderer::ObjectManager object_manager_;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    constexpr Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    SDL_Window *window_ = SDL_CreateWindow("Alice Code", 1280, 720, window_flags);

    SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    void *gl_context_ = SDL_GL_CreateContext(window_);
    SDL_GL_MakeCurrent(window_, gl_context_);

    SDL_ShowWindow(window_);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplSDL3_InitForOpenGL(window_, gl_context_);
    ImGui_ImplOpenGL3_Init();

    alice::renderer::Framebuffer framebuffer_;

    object_manager_.Add(std::make_shared<alice::renderer::ObjectTriangle>());

    alice::game::framework::World world_;

    while (alice::core::App::GetSingleton().running) {
        if (SDL_Event event; SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                alice::core::App::GetSingleton().running = false;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("World");

        if (ImGui::IsMouseReleased(1)) {
            ImGui::OpenPopup("Window");
        }

        for (const auto &space: world_.GetSpaces()) {
            DrawEntity(space);
        }

        if (ImGui::BeginPopupContextWindow()) {
            if (ImGui::Button("Create Space")) {
                const auto space = alice::game::framework::SpaceClassFactory::Create("Space");

                world_.Join(space);
            }
            ImGui::EndPopup();
        }

        ImGui::End();

        ImGui::Begin("My Scene");

        const float width = ImGui::GetContentRegionAvail().x;
        const float height = ImGui::GetContentRegionAvail().y;

        object_manager_.SetViewport(width, height);

        framebuffer_.Texture(width, height);

        ImGui::Image(
            (void *) framebuffer_.GetTexture(),
            ImVec2{width, height},
            ImVec2(0, 1),
            ImVec2(1, 0)
        );

        ImGui::End();

        ImGui::Render();

        framebuffer_.Bind();

        glClear(GL_COLOR_BUFFER_BIT);

        object_manager_.Draw();

        framebuffer_.UnBind();

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window_);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}
