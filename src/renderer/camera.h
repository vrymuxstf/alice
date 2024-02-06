#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

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
        glm::vec3 rotation{0.0f, 0.0f, 0.0f};

        [[nodiscard]] glm::quat GetOrientation() const {
            glm::quat pitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1, 0, 0));
            glm::quat yaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0, 1, 0));

            return glm::normalize(pitch * yaw);
        }

        [[nodiscard]] glm::mat4 GetView() const {
            return glm::mat4_cast(GetOrientation());
        }

        [[nodiscard]] glm::mat4 GetProjection() const {
            return glm::perspective(
                    glm::radians(45.0f),
                    (float) width / (float) height,
                    0.1f,
                    100.f
            );
        }

        [[nodiscard]] glm::mat4 GetViewProjection() const {
            return GetProjection() * GetView();
        }
    };
}
