#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
  float yValue = gl_FragCoord.y / 500.0f;

  color = mix(u_Color, vec4(0.2f, 0.1f, 0.8f, 1.0f), yValue);
}
