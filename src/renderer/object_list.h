#pragma once

#include <algorithm>
#include <vector>

namespace alice {
    template<class BaseObjectClass>
    class ObjectList {
        std::vector<BaseObjectClass *> objects;
    public:
        ~ObjectList() {
            for (auto *object: objects) {
                delete object;
            }
            objects.clear();
        }

        template<class ObjectClass, typename ... Args>
        ObjectClass *Create(Args ... args) {
            auto new_object = new ObjectClass(args ...);
            objects.push_back(new_object);
            return new_object;
        }

        void Destroy(BaseObjectClass *object) {
            objects.erase(
                    std::remove(objects.begin(), objects.end(), object),
                    objects.end()
            );
            delete object;
        }

        std::vector<BaseObjectClass *>::iterator begin() {
            return objects.begin();
        }

        std::vector<BaseObjectClass *>::iterator end() {
            return objects.end();
        }

        std::vector<BaseObjectClass *> Get() {
            return objects;
        }
    };
}