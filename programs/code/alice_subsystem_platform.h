#pragma once

#include <iostream>

#include "alice/core/app.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <alice/renderer/object_manager.h>
#include <alice/renderer/object_triangle.h>

#include "object_im_gui.h"

class AliceSubsystemPlatform final : public alice::core::Subsystem {
    SDL_Window *window_;
    void *gl_context_;
    alice::renderer::ObjectManager object_manager_;

public:
    explicit AliceSubsystemPlatform(alice::core::App *app): Subsystem(app) {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        constexpr Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
        window_ = SDL_CreateWindow("Alice Code", 1280, 720, window_flags);

        SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        gl_context_ = SDL_GL_CreateContext(window_);
        SDL_GL_MakeCurrent(window_, gl_context_);

        SDL_ShowWindow(window_);

        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));

        object_manager_.Add(std::make_shared<alice::renderer::ObjectTriangle>());

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        object_manager_.Add(std::make_shared<alice::ObjectImGui>());

        ImGui_ImplSDL3_InitForOpenGL(window_, gl_context_);
    }

    ~AliceSubsystemPlatform() override {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        SDL_GL_DeleteContext(gl_context_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    void Update() override {
        if (SDL_Event event; SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                alice::core::App::GetSingleton().running = false;
            }
        }

        ImGui_ImplSDL3_NewFrame();

        const auto io = ImGui::GetIO();

        object_manager_.SetViewport(io.DisplaySize.x, io.DisplaySize.y);

        object_manager_.Draw();

        SDL_GL_SwapWindow(window_);
    }
};
