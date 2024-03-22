#pragma once

#include "shader.h"

namespace alice {
    class SkyboxShader : public Shader {
    public:
        static SkyboxShader &Singleton() {
            static SkyboxShader instance;
            return instance;
        }

        SkyboxShader();
    };
}