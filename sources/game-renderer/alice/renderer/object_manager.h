#pragma once

#include <iostream>

#include <memory>
#include <vector>

#include "object.h"

#include <glad/glad.h>

namespace alice::renderer {
    class ObjectManager {
        std::vector<std::shared_ptr<Object> > objects_;
        float last_viewport_width_ = 0;
        float last_viewport_height_ = 0;

    public:
        void Add(const std::shared_ptr<Object> &object) {
            objects_.push_back(object);
        }

        void Remove(const std::shared_ptr<Object> &object) {
            std::erase(objects_, object);
        }

        bool SetViewport(const float width, const float height) {
            if (last_viewport_width_ == width && last_viewport_height_ == height) return false;

            last_viewport_width_ = width;
            last_viewport_height_ = height;

            glViewport(0, 0, static_cast<int>(last_viewport_width_), static_cast<int>(last_viewport_height_));

            return true;
        }

        void Draw() const {
            for (const auto &object: objects_) {
                object->Draw();
            }
        }
    };
}
