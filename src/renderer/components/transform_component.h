#pragma once

#include "component.h"

namespace alice {
    class TransformComponent : public Component {
    public:
        using Component::Component;

        std::string GetClassName() override {
            return "TransformComponent";
        }
    };
}