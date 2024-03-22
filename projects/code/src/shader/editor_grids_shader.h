#pragma once

#include "shader.h"

namespace alice {
    class EditorGridsShader : public Shader {
    public:
        static EditorGridsShader &Singleton() {
            static EditorGridsShader instance;
            return instance;
        }

        EditorGridsShader();
    };
}