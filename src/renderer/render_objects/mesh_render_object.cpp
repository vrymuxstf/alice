#include "mesh_render_object.h"

#include "shader/mesh_shader.h"

#include "camera.h"

#ifdef OPENGL

#include "glad/glad.h"
#include "singleton.h"

#endif

namespace alice {
    MeshRenderObject::MeshRenderObject(const std::vector<MeshVertex> &vertices, const std::vector<uint32_t> &indices)
            : count_(indices.size()) {
#ifdef OPENGL
        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glGenBuffers(1, &vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (vertices.size() * sizeof(MeshVertex)), vertices.data(),
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) offsetof(MeshVertex, Position));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) offsetof(MeshVertex, Normal));
        glEnableVertexAttribArray(2);

        glGenBuffers(1, &ebo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                (GLsizeiptr) (indices.size() * sizeof(uint32_t)),
                indices.data(),
                GL_STATIC_DRAW
        );
#endif
    }

    void MeshRenderObject::Draw() {
        Singleton<MeshShader>().Use();

        Singleton<MeshShader>().SetMat4("u_ViewProjection", Camera::Singleton().GetViewProjection());
#ifdef OPENGL
        glBindVertexArray(vao_);
        glDrawElements(GL_TRIANGLES, (GLsizei) count_, GL_UNSIGNED_INT, nullptr);
#endif
    }
}