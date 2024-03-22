#include "alice/program.h"

namespace alice {
    std::function<Program *()> Program::CreateProgramFunc = []() { return new Program; };

    void Program::Run() {
        while (Running) {
            Update();
        }
    }
}

int main() {
    auto program = alice::Program::CreateProgramFunc();
    program->Run();
    delete program;
    return 0;
}