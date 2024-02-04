#pragma once

#include "render_object.h"

namespace alice {
    class TriangleRenderObject : public RenderObject {
        unsigned int vao_{};
        unsigned int vbo_{};
    public:
        TriangleRenderObject(float* data, size_t size);

        void Draw() override;
    };
}