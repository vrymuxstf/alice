#pragma once

#include "component.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

namespace alice {
    class TransformComponent : public Component {
        glm::vec3 translation{0.0f};
        glm::vec3 rotation{0.0f};
        glm::vec3 scale{1.0f};
        glm::mat4 transform_{1.0f};
    public:
        using Component::Component;

        std::string GetClassName() override {
            return "TransformComponent";
        }

        [[nodiscard]] const glm::mat4 &GetTransform() const { return transform_; }

        void DisplayImGui() override {
            ImGui::DragFloat3("Translation", glm::value_ptr(translation));
            ImGui::DragFloat3("Rotation", glm::value_ptr(rotation));
            ImGui::DragFloat3("Scale", glm::value_ptr(scale));
        }

        void Update(float delta_time) override {
            glm::mat4 transform(1.0f);

            transform = glm::translate(transform, translation);
            transform = glm::scale(transform, scale);

            transform_ = transform;
        }
    };
}