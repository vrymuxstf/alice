#pragma once

#include <iostream>

#include <string>
#include <unordered_map>
#include <functional>

namespace alice::game::framework {
    class Space;

    using space_class_initializer = std::function<Space*()>;

    class SpaceClassFactory {
    public:
        std::unordered_map<std::string, space_class_initializer> space_class_initializers;

        static SpaceClassFactory &GetSingleton() {
            static SpaceClassFactory singleton;
            return singleton;
        }

        static Space *Create(const std::string &name) {
            return GetSingleton().space_class_initializers[name]();
        }
    };

    template<class SpaceClass>
    class SpaceClassRegistrant {
    public:
        explicit SpaceClassRegistrant(const std::string &name) {
            SpaceClassFactory::GetSingleton().space_class_initializers[name] = [name]() {
                return new SpaceClass(name);
            };
        }

        static void Print() {
            for (const auto &key: SpaceClassFactory::GetSingleton().space_class_initializers | std::views::keys) {
                std::cout << key << std::endl;
            }
        }
    };
}
