#pragma once

#include "glm/glm.hpp"

namespace alice {
    struct MeshVertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };
}