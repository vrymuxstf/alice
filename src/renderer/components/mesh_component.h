#pragma once

#include "component.h"

#include "mesh_reader.h"
#include "render_objects/mesh_render_object.h"

namespace alice {
    class MeshComponent : public Component {
        MeshRenderObject *mesh_;
    public:
        explicit MeshComponent(Entity *owner);

        ~MeshComponent() override;

        std::string GetClassName() override {
            return "MeshComponent";
        }
    };
}