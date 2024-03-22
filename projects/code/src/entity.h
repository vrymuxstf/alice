#pragma once

#include <string>
#include <vector>

namespace alice {
    class Entity;

    struct EntityProperties {
        Entity *owner = nullptr;
        std::string type_name;
        std::string name = "UNKNOWN";
    };

    class Entity {
        Entity *owner_ = nullptr;
        std::string type_name_;
        std::string name_;
        std::vector<Entity *> dependencies_;
    public:
        explicit Entity(const EntityProperties &properties = {}) :
                owner_(properties.owner),
                type_name_(properties.type_name),
                name_(properties.name) {

        }

        virtual ~Entity() {
            for (auto *dependency: dependencies_) {
                delete dependency;
            }
            dependencies_.clear();
        }

        template<class EntityClass, typename ... Args>
        void CreateDependency(EntityProperties properties = {}, Args ... args) {
            properties.owner = this;
            auto new_dependency = new EntityClass(properties, args ...);
            dependencies_.push_back(new_dependency);
        }

        void DeleteDependency(Entity *&dependency) {
            dependencies_.erase(
                    std::remove(dependencies_.begin(), dependencies_.end(), dependency),
                    dependencies_.end()
            );
            delete dependency;
            dependency = nullptr;
        }

        [[nodiscard]] std::vector<Entity *> GetDependencies() const { return dependencies_; }

        [[nodiscard]] const std::string &GetName() const { return name_; }

        [[nodiscard]] Entity *GetOwner() const { return owner_; }

        virtual void Update(float delta_time) {}

        virtual void DisplayImGui() {}
    };
}