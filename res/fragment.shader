#version 330 core

layout(location = 0) out vec4 outputColor;

uniform sampler2D u_texture;
in vec2 v_TexCoord;

void main()
{
  vec4 texColor = texture(u_texture, v_TexCoord);
  outputColor = texColor;
  /* outputColor = vec4(1.0,0.0,0.0,1.0); */
}
