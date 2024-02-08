#pragma once

#include "shader.h"

namespace alice {
    class TriangleShader : public Shader {
    public:
        static TriangleShader &Singleton() {
            static TriangleShader instance;
            return instance;
        }

        TriangleShader();
    };
}