#include "mesh_component.h"

#include "entity.h"
#include "engine.h"

namespace alice {
    MeshComponent::MeshComponent(Entity *owner) : Component(owner) {
        MeshReader mesh_reader;
        mesh_reader.Read("assets/mesh.fbx");
        mesh_ = Engine::Singleton().GetRenderObjectList().Create<MeshRenderObject>(
                mesh_reader.vertices,
                mesh_reader.indices
        );
    }

    MeshComponent::~MeshComponent() {
        Engine::Singleton().GetRenderObjectList().Destroy(mesh_);
    }

    void MeshComponent::Update(float delta_time) {
        auto transform_comp = (TransformComponent *) GetOwner()->GetComponent("TransformComponent");
        if (transform_comp) {
            mesh_->UpdateTransform(transform_comp->GetTransform());
        }
    }
}