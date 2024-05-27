#pragma once

namespace alice::renderer {
    class Object {
    public:
        virtual ~Object() = default;

        virtual void Draw() = 0;
    };
}
