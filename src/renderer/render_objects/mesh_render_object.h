#pragma once

#include <vector>

#include "render_object.h"

#include "mesh.h"

namespace alice {

    class MeshRenderObject : public RenderObject {
        unsigned int vao_{};
        unsigned int vbo_{};
        unsigned int ebo_{};
        unsigned int count_;
    public:
        MeshRenderObject(const std::vector<MeshVertex>& vertices, const std::vector<uint32_t>& indices);

        void Draw() override;
    };
}