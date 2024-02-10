#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>

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

        [[nodiscard]] glm::quat GetOrient() const {
            auto yaw = glm::angleAxis(glm::radians(-rotation.y), glm::vec3(0, 1, 0));
            auto pitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1, 0, 0));
            return yaw * pitch;
        }

        [[nodiscard]] glm::vec3 GetForward() const {
            glm::vec3 orient(0, 0, -1);
            return GetOrient() * orient;
        }

        [[nodiscard]] glm::mat4 GetView() const {
            return glm::inverse(glm::mat4_cast(GetOrient())) * glm::translate(glm::mat4(1.0f), -position);
            //return glm::lookAt(position, position + GetForward(), glm::vec3(0, 1, 0));
        }

        [[nodiscard]] glm::mat4 GetProjection() const {
            return glm::perspective(
                    glm::radians(45.0f),
                    (float) width / (float) height,
                    0.1f,
                    1000.0f
            );
        }

        [[nodiscard]] glm::mat4 GetViewProjection() const {
            return GetProjection() * GetView();
        }

        [[nodiscard]] glm::vec3 GetRight() const {
            return glm::normalize(glm::cross(GetForward(), glm::vec3(0, 1, 0)));
        }

        [[nodiscard]] glm::vec3 GetPosition() const {
            return position;
        }
    };
}