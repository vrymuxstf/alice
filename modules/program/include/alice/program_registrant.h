#pragma once

#include "program.h"

namespace alice {
    template<class T>
    class ProgramRegistrant {
    public:
        ProgramRegistrant() {
            Program::CreateProgramFunc = []() {
                return new T;
            };
        }
    };
}

