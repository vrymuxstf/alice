#pragma once

#include <string>

#include "vector.h"

#include "json.hpp"

namespace alice::game::framework {
    class Property {
        std::string name_;

    public:
        explicit Property(const std::string &name) : name_(name) {
        }

        virtual ~Property() = default;

        [[nodiscard]] const std::string &GetName() const { return name_; }

        virtual void In(const std::string &a) = 0;

        virtual std::string Out() = 0;
    };

    template<typename T>
    class PropertyType : public Property {
        T default_value_;

    protected:
        T value_;

    public:
        PropertyType(const std::string &name, T default_value)
            : Property(name), default_value_(default_value), value_(default_value_) {
        }

        T *GetValuePtr() { return &value_; }
    };

    class PropertyString final : public PropertyType<std::string> {
    public:
        using PropertyType::PropertyType;

        void In(const std::string &a) override {
            value_ = a;
        }

        std::string Out() override {
            return value_;
        }
    };

    class PropertyVector final : public PropertyType<Vector> {
    public:
        using PropertyType::PropertyType;

        void In(const std::string &a) override {
            nlohmann::json j = nlohmann::json::parse(a);

            value_.x = j["x"];
            value_.y = j["y"];
            value_.z = j["z"];
        }

        std::string Out() override {
            nlohmann::json j;

            j["x"] = value_.x;
            j["y"] = value_.y;
            j["z"] = value_.z;

            return j.dump();
        }
    };
}
