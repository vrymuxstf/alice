#pragma once

#include <string>
#include <vector>

#include "component.h"

namespace alice {
    class ComponentFactory {
    public:
        static std::vector<std::string> GetComponentNames() {
            return {"TransformComponent", "MeshComponent"};
        }
    };
}