#version 330 core

out vec4 FragColor;

uniform sampler2D u_texture;
uniform sampler2D u_texture2;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

in vec2 v_TexCoord;
in vec3 Normal;
in vec3 FragPos;

void main()
{
  float ambientStrength = 0.3;
  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  float specularStrength = 0.5;
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightColor;  

  vec4 texColor = texture(u_texture, v_TexCoord);
  vec4 texColor2 = texture(u_texture2, v_TexCoord);
  vec3 result = (ambient + diffuse) * vec3(texColor) + specular * vec3(texColor2);
  /* for(int i = 0; i < 3; i++){ */
  /*   result[i] = round(result[i]*8)/8; */
  /* } */
  FragColor = vec4(result, 1.0);
}
  /* vec3 result = ambient * objectColor; */
  /* FragColor = vec4(result, 1.0); */
  /* vec4 texColor = mix(texture(u_texture, v_TexCoord), texture(u_texture2, v_TexCoord), 0.2); */
  /* outputColor = texColor; */
