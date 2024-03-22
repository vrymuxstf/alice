#pragma once

#include "render_object.h"
#include "textures/cube_map.h"

namespace alice {
    class SkyboxRenderObject : public RenderObject {
        unsigned int vao_{};
        unsigned int vbo_{};
        CubeMap cube_map_{
                {
                        "assets/right.jpg",
                        "assets/left.jpg",
                        "assets/top.jpg",
                        "assets/bottom.jpg",
                        "assets/front.jpg",
                        "assets/back.jpg"
                }
        };
    public:
        SkyboxRenderObject();

        void Draw() override;
    };
}