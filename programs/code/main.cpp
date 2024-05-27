#include "alice/core/app.h"

#include "alice_subsystem_platform.h"

int main(int, char **) {
    auto &app = alice::core::App::GetSingleton();
    app.Add<AliceSubsystemPlatform>();
    app.Run();

    return 0;
}
