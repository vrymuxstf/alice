#include "triangle_render_object.h"

#include "singleton.h"
#include "triangle_shader.h"

#ifdef OPENGL
#include <glad/glad.h>
#endif

namespace alice {
    TriangleRenderObject::TriangleRenderObject(float *data, size_t size) {
#ifdef OPENGL
        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glGenBuffers(1, &vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) size, data, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
#endif
    }

    void TriangleRenderObject::Draw() {
        Singleton<TriangleShader>().Use();
#ifdef OPENGL
        glBindVertexArray(vao_);
        glDrawArrays(GL_TRIANGLES, 0, 3);
#endif
    }
}