#pragma once

#include <vector>
#include <memory>

namespace alice {
    class Object {
    };

    template<class ContainerClass>
    class Slot {
        std::shared_ptr<ContainerClass> container_;
    };

    template<class SlotClass>
    class Container {
        std::vector<std::shared_ptr<SlotClass> > slots_;
    };
}
