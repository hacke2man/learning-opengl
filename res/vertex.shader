#version 330 core

layout(location = 0) in vec3 position;
/* layout(location = 1) in vec2 texCoord; */
layout(location = 1) in vec3 normal;

out vec2 v_TexCoord;
out vec3 aNormal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    aNormal = normal;
    /* v_TexCoord = texCoord; */
    FragPos = vec3(model * vec4(position, 1.0));
}
