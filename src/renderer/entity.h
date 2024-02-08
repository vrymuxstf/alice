#pragma once

#include <string>
#include <vector>

#include "component.h"
#include "components/transform_component.h"
#include "components/mesh_component.h"

namespace alice {
    class Entity {
        std::vector<Component *> components_;
    public:
        ~Entity() {
            for (auto *component: components_) {
                delete component;
            }
            components_.clear();
        }

        Component *CreateComponent(const std::string &name) {
            Component *new_component = nullptr;

            if (name == "TransformComponent") {
                new_component = new TransformComponent(this);
            }

            if (name == "MeshComponent") {
                new_component = new MeshComponent(this);
            }

            if (new_component) {
                components_.push_back(new_component);
                return new_component;
            }

            return nullptr;
        }

        void DestroyComponent(Component *component) {
            components_.erase(
                    std::remove(components_.begin(), components_.end(), component),
                    components_.end()
            );
            delete component;
        }

        [[nodiscard]] std::vector<Component *> GetComponent() const { return components_; }
    };
}