#include "mesh_shader.h"

namespace {
    const char *vertex_shader_src = R"(
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}
)";

    const char *fragment_shader_src = R"(
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";
}

namespace alice {
    MeshShader::MeshShader() : Shader(vertex_shader_src, fragment_shader_src) {

    }
}