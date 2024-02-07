#include "skybox_shader.h"

namespace {
    const char *vertex_shader_src = R"(
#version 330 core
layout (location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
    v_TexCoords = a_Position;
    vec4 position = u_Projection * u_View * vec4(a_Position, 1.0);
    gl_Position = position.xyww;
}
)";

    const char *fragment_shader_src = R"(
#version 330 core
out vec4 color;

in vec3 v_TexCoords;

uniform samplerCube u_Skybox;

void main()
{
    color = texture(u_Skybox, v_TexCoords);
}
)";
}

namespace alice {
    SkyboxShader::SkyboxShader() : Shader(vertex_shader_src, fragment_shader_src) {

    }
}