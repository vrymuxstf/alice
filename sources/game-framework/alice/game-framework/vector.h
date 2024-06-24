#pragma once

namespace alice::game::framework {
    struct Vector {
        float x = 0;
        float y = 0;
        float z = 0;

        float *operator*() {
            return &x;
        }

        const float* operator*() const {
            return &x;
        }
    };
}
