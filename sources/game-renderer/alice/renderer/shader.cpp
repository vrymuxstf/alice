#include <iostream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#include "glad/glad.h"

namespace alice::renderer {
    Shader::Shader(const char *vertex_shader_src, const char *fragment_shader_src) {

        auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertex_shader, 1, &vertex_shader_src, nullptr);

        glCompileShader(vertex_shader);

        GLint isCompiled = 0;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertex_shader);

            std::cerr << infoLog.data();

            return;
        }

        auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragment_shader, 1, &fragment_shader_src, nullptr);

        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            std::cerr << infoLog.data();

            return;
        }

        program_ = glCreateProgram();

        glAttachShader(program_, vertex_shader);
        glAttachShader(program_, fragment_shader);

        glLinkProgram(program_);

        GLint isLinked = 0;
        glGetProgramiv(program_, GL_LINK_STATUS, (int *) &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program_, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program_);
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            std::cerr << infoLog.data();

            return;
        }

        glDetachShader(program_, vertex_shader);
        glDetachShader(program_, fragment_shader);
    }

    void Shader::Use() const {
        glUseProgram(program_);
    }

    void Shader::SetMat4(const char *name, const glm::mat4 &value) const {
        const auto location = glGetUniformLocation(program_, name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetVec3(const char *name, const glm::vec3 &value) const {
        const auto location = glGetUniformLocation(program_, name);
        glUniform3f(location, value.x, value.y, value.z);
    }
}