#include "triangle_shader.h"

namespace {
    const char *vertex_shader_src = R"(
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_Model;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
    v_Color = a_Color;
}
)";

    const char *fragment_shader_src = R"(
#version 330 core

in vec4 v_Color;

out vec4 color;

void main()
{
    color = v_Color;
}
)";
}

namespace alice {
    TriangleShader::TriangleShader() : Shader(vertex_shader_src, fragment_shader_src) {

    }
}