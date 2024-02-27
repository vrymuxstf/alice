#pragma once

#include "entity.h"

#include "engine.h"

#include "mesh_reader.h"
#include "render_objects/mesh_render_object.h"

#include "transform.h"

namespace alice {
    class Mesh : public Transform {
        MeshRenderObject *mesh_;
    public:
        explicit Mesh(const EntityProperties &properties) : Transform(properties) {
            MeshReader mesh_reader;
            mesh_reader.Read("assets/mesh.fbx");
            mesh_ = Engine::Singleton().GetRenderObjectList().Create<MeshRenderObject>(
                    mesh_reader.vertices,
                    mesh_reader.indices
            );
        }

        ~Mesh() override {
            Engine::Singleton().GetRenderObjectList().Destroy(mesh_);
        }

        void Update(float delta_time) override {
            mesh_->UpdateTransform(GetTransform());
        }
    };
}