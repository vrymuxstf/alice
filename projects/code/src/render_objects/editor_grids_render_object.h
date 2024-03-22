#pragma once

#include "render_object.h"

namespace alice {
    class EditorGridsRenderObject : public RenderObject {
        unsigned int vao_{};
        unsigned int vbo_{};
        int size{};
    public:
        EditorGridsRenderObject();

        void Draw() override;
    };
}