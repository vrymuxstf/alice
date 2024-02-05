#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace alice {
    class Camera {
    public:
        static Camera &Singleton() {
            static Camera instance;
            return instance;
        }

        int width = 1;
        int height = 1;
        glm::vec3 position{0.0f, 0.0f, 10.0f};

        [[nodiscard]] glm::mat4 GetViewProjection() const {
            glm::mat4 projection = glm::perspective(
                    glm::radians(45.0f),
                    (float) width / (float) height,
                    0.1f,
                    100.f
            );
            glm::mat4 view = glm::lookAt(position, {0.0f, 0.0f, -1}, {0.0f, 1.0f, 0});
            return projection * view;
        }
    };
}