#pragma once

#include <memory>

#include "object.h"
#include "shader.h"

namespace alice::renderer {
    class ObjectTriangle final : public Object {
        std::shared_ptr<Shader> shader_;
        unsigned int VAO = 0;

    public:
        ObjectTriangle() {
            const auto vertexShaderSource = "#version 330 core\n"
                    "layout (location = 0) in vec3 aPos;\n"
                    "void main()\n"
                    "{\n"
                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                    "}\0";

            const auto fragmentShaderSource = "#version 330 core\n"
                    "out vec4 FragColor;\n"
                    "void main()\n"
                    "{\n"
                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                    "}\n\0";

            shader_ = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource);

            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            constexpr float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
            };

            unsigned int VBO;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
            glEnableVertexAttribArray(0);
        }

        void Draw() override {
            shader_->Use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    };
}
