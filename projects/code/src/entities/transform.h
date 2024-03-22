#pragma once

#include "entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

namespace alice {
    class Transform : public Entity {
        glm::vec3 translation{0.0f};
        glm::vec3 rotation{0.0f};
        glm::vec3 scale{1.0f};
    public:
        using Entity::Entity;

        [[nodiscard]] glm::mat4 GetTransform() const {
            glm::mat4 transform(1.0f);

            if (auto parent_transform = dynamic_cast<Transform *>(GetOwner())) {
                transform = parent_transform->GetTransform();
            }

            transform = glm::translate(transform, translation);
            transform = glm::scale(transform, scale);

            return transform;
        }

        void DisplayImGui() override {
            ImGui::DragFloat3("Translation", glm::value_ptr(translation));
            ImGui::DragFloat3("Rotation", glm::value_ptr(rotation));
            ImGui::DragFloat3("Scale", glm::value_ptr(scale));
        }
    };
}