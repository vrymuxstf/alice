#pragma once

#include <vector>

#include "property_types.h"
#include "space_class_registrant.h"

namespace alice::game::framework {
    class World;

    class Space {
        friend class World;

        std::string class_name_;
        std::vector<Property *> properties_;
        World *world_ = nullptr;

        PropertyString tag_{"Tag", ""};
        PropertyVector location_{"Location", {0, 0, 0}};
        PropertyVector rotation_{"Rotation", {0, 0, 0}};
        PropertyVector scale_{"Scale", {1, 1, 1}};

    public:
        explicit Space(const std::string &class_name)
            : class_name_(class_name), properties_{&tag_, &location_, &rotation_, &scale_} {
        }

        virtual ~Space() = default;

        [[nodiscard]] const std::vector<Property *> &GetProperties() const { return properties_; }

        virtual void Update() {
        }

        virtual void OnJoin() {
        }

        virtual void OnLeave() {
        }
    };

    inline SpaceClassRegistrant<Space> SpaceClassRegistrantSpace("Space");
}
