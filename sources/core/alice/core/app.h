#pragma once

#include <iostream>
#include <vector>

#include "subsystem.h"

namespace alice::core {
    class App {
        std::vector<Subsystem *> subsystems_;

    public:
        bool running = true;

        static App &GetSingleton() {
            static App app;
            return app;
        }

        ~App() {
            for (const auto &subsystem: subsystems_) {
                delete subsystem;
            }
        }

        template<class T>
        void Add() {
            subsystems_.push_back(new T(this));
        }

        void Run() const {
            while (running) {
                for (const auto &subsystem: subsystems_) {
                    subsystem->Update();
                }

                //std::cout << running << std::endl;
            }
        }
    };
}
