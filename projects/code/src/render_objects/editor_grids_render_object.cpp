#include <cmath>
#include <vector>

#include "editor_grids_render_object.h"

#include "shader/editor_grids_shader.h"

#include <glad/glad.h>

#include "camera.h"

namespace alice {
    EditorGridsRenderObject::EditorGridsRenderObject() {
        const int gridSize = 500;  // 10x10 grid
        const float spacing = 1.0f; // 1 unit between lines

        std::vector<float> gridVertices;
        for (int i = -gridSize; i <= gridSize; ++i) {
            gridVertices.push_back(i * spacing); // x
            gridVertices.push_back(0);           // y
            gridVertices.push_back(-gridSize * spacing); // z start

            gridVertices.push_back(i * spacing); // x
            gridVertices.push_back(0);           // y
            gridVertices.push_back(gridSize * spacing); // z end

            // Horizontal line
            gridVertices.push_back(-gridSize * spacing); // x start
            gridVertices.push_back(0);           // y
            gridVertices.push_back(i * spacing); // z

            gridVertices.push_back(gridSize * spacing); // x end
            gridVertices.push_back(0);           // y
            gridVertices.push_back(i * spacing); // z
        }

        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glGenBuffers(1, &vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), &gridVertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        size = gridVertices.size();
    }

    void EditorGridsRenderObject::Draw() {
        EditorGridsShader::Singleton().Use();

        auto pos = Camera::Singleton().GetPosition();
        pos.x = std::round(pos.x / 1);
        pos.z = std::round(pos.z / 1);
        pos.y = 0;

        EditorGridsShader::Singleton().SetMat4("u_ViewProjection", Camera::Singleton().GetViewProjection());
        EditorGridsShader::Singleton().SetMat4("u_Transform", glm::translate(glm::mat4(1.0f), pos));

        glBindVertexArray(vao_);
        glDrawArrays(GL_LINES, 0, size / 3);
    }
}