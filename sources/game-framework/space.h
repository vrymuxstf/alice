#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

namespace alice {
    class Space : public std::enable_shared_from_this<Space> {
    public:
        class Component : public std::enable_shared_from_this<Component> {
            std::shared_ptr<Space> owner_ = nullptr;

        public:
            explicit Component(const std::shared_ptr<Space> &owner): owner_(owner) {
                owner_->components_.push_back(this);
            }

            virtual ~Component() = default;

            virtual void Update() {
            }
        };

    private:
        std::shared_ptr<Space> super_ = nullptr;
        std::vector<std::shared_ptr<Space> > subs_;
        std::vector<std::shared_ptr<Component> > components_;
        glm::mat4 transform_ = 1.0f;

    public:
        void Attach(const std::shared_ptr<Space> &super) {
            Detach();
            super_ = super;
            super->subs_.push_back(shared_from_this());
        }

        void Detach() {

        }

        void Update() {
            for (const auto &component: components_) {
                component->Update();
            }

            for (const auto &sub: subs_) {
                sub->Update();
            }
        }
    };
}
