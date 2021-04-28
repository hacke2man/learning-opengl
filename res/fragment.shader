#version 330 core

layout(location = 0) out vec4 outputColor;

uniform sampler2D u_texture;
uniform sampler2D u_texture2;
in vec2 v_TexCoord;

void main()
{
  vec4 texColor = mix(texture(u_texture, v_TexCoord), texture(u_texture2, v_TexCoord), 0.2);
  outputColor = texColor;
  /* outputColor = vec4(1.0,0.0,0.0,1.0); */
}
