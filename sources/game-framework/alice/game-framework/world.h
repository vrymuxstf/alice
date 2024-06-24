#pragma once

#include <vector>

#include "space.h"

namespace alice::game::framework {
    class World {
        std::vector<Space *> spaces_;

    public:
        void Join(Space *space) {
            if (space->world_) return;
            spaces_.push_back(space);
            space->world_ = this;
            space->OnJoin();
        }

        void Leave(Space *space) {
            if (space->world_ != this) return;
            space->OnLeave();
            space->world_ = nullptr;
            std::erase(spaces_, space);
        }

        void Update() {
            for (const auto &space: spaces_) {
                space->Update();
            }
        }

        [[nodiscard]] const std::vector<Space *> &GetSpaces() const { return spaces_; }
    };
}
