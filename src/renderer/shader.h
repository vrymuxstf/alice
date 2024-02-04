#pragma once

#include <cstdint>

#include "singleton.h"

namespace alice {
    class Shader {
        uint32_t program_ = 0;
    public:
        Shader(const char *vertex, const char *fragment);

        void Use() const;

        [[nodiscard]] uint32_t GetProgram() const { return program_; }
    };
}