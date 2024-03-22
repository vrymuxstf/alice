#pragma once

#include "shader.h"

namespace alice {
    class MeshShader : public Shader {
    public:
        static MeshShader &Singleton() {
            static MeshShader instance;
            return instance;
        }

        MeshShader();
    };
}