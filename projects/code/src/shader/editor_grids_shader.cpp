#include "editor_grids_shader.h"

namespace {
    const char *vertex_shader_src = R"(
#version 330 core
layout (location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}
)";

    const char *fragment_shader_src = R"(
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0, 1.0, 1.0, 0.5);
}
)";
}

namespace alice {
    EditorGridsShader::EditorGridsShader() : Shader(vertex_shader_src, fragment_shader_src) {
    }
}