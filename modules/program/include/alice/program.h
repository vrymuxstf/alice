#pragma once

#include <functional>

namespace alice {
    class Program {
    public:
        static std::function<Program *()> CreateProgramFunc;

        bool Running = true;

        void Run();

        virtual void Update() {}
    };
}