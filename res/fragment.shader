#version 330 core

layout(location = 0) out vec4 FragColor;

/* uniform sampler2D u_texture; */
/* uniform sampler2D u_texture2; */
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
/* in vec2 v_TexCoord; */
in vec3 aNormal;
in vec3 FragPos;

void main()
{
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(aNormal);
  vec3 lightDir = normalize(lightPos - FragPos);  
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse) * objectColor;
  FragColor = vec4(result, 1.0);
}
  /* vec3 result = ambient * objectColor; */
  /* FragColor = vec4(result, 1.0); */
  /* vec4 texColor = mix(texture(u_texture, v_TexCoord), texture(u_texture2, v_TexCoord), 0.2); */
  /* outputColor = texColor; */
