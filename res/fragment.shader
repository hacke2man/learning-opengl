#version 330 core

layout(location = 0) out vec4 outputColor;

uniform sampler2D u_texture;
in vec2 v_TexCoord;

void main()
{
<<<<<<< HEAD
  vec4 texColor = texture(u_texture, v_TexCoord);
  outputColor = texColor;
  /* outputColor = vec4(1.0,0.0,0.0,1.0); */
=======
  float yValue = gl_FragCoord.y / 500.0f;

  color = mix(u_Color, vec4(0.2f, 0.1f, 0.8f, 1.0f), yValue);
>>>>>>> f1793e6864c06aa969201bf09d90f6c39ae6df16
}
