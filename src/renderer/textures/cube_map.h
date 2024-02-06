#pragma once

#include <array>

namespace alice {
    class CubeMap {
        unsigned int id_ = 0;
    public:
        explicit CubeMap(const std::array<const char *, 6> &textures);

        void Use() const;
    };
}