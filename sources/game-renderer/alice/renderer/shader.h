#pragma once

#include <cstdint>

#include <glm/glm.hpp>

namespace alice::renderer {
    class Shader {
        uint32_t program_ = 0;
    public:
        Shader(const char *vertex_shader_src, const char *fragment_shader_src);

        void Use() const;

        void SetMat4(const char *name, const glm::mat4 &value) const;

        void SetVec3(const char *name, const glm::vec3 &value) const;
    };
}