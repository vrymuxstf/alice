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
}