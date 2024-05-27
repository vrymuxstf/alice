#pragma once

#include "imgui_impl_opengl3.h"

#include "alice/renderer/object.h"

namespace alice {
    class ObjectImGui final : public renderer::Object {
    public:
        ObjectImGui() {
            ImGui_ImplOpenGL3_Init();
        }

        void Draw() override {
            ImGui_ImplOpenGL3_NewFrame();

            ImGui::NewFrame();

            ImGui::ShowDemoWindow();

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    };
}
