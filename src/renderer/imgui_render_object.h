#pragma once

#include "render_object.h"

namespace alice {
    class ImGuiRenderObject : public RenderObject {
    public:
        ImGuiRenderObject();
        void Draw() override;
    };
}