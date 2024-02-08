#pragma once

#include <string>

#include "imgui.h"

namespace alice {
    class Entity;

    class Component {
        Entity *owner_;
    public:
        explicit Component(Entity *owner) : owner_(owner) {}

        virtual ~Component() = default;

        Entity *GetOwner();

        virtual std::string GetClassName() { return "Component"; }

        virtual void DisplayImGui() {
        }

        virtual void Update(float delta_time) {

        }
    };
}