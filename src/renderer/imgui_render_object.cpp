#include "imgui_render_object.h"

#include "opengl/imgui_impl_opengl3.h"

namespace alice {
    void ImGuiRenderObject::Draw() {
#ifdef OPENGL
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
    }

    ImGuiRenderObject::ImGuiRenderObject() {
    }
}