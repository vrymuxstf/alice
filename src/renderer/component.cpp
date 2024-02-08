#pragma once

#include "component.h"

namespace alice {
    Entity *alice::Component::GetOwner() {
        return owner_;
    }
}