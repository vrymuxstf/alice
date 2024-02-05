#include "triangle_shader.h"

namespace {
    const char *vertex_shader_src = R"(
#version 330 core
layout (location = 0) in vec3 a_Position;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
}
)";

    const char *fragment_shader_src = R"(
#version 330 core

out vec4 color;

void main()
{
    color = vec4(0.5, 0.5, 0.2, 1.0);
}
)";
}

namespace alice {
    TriangleShader::TriangleShader() : Shader(vertex_shader_src, fragment_shader_src) {

    }
}