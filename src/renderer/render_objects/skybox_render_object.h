#pragma once

#include "render_object.h"
#include "textures/cube_map.h"

namespace alice {
    class SkyboxRenderObject : public RenderObject {
        unsigned int vao_{};
        unsigned int vbo_{};
        CubeMap cube_map_{
                {
                        "right.jpg",
                        "left.jpg",
                        "top.jpg",
                        "bottom.jpg",
                        "front.jpg",
                        "back.jpg"
                }
        };
    public:
        SkyboxRenderObject();

        void Draw() override;
    };
}