#version 330 core

out vec4 FragColor;

uniform sampler2D u_texture;
uniform sampler2D u_texture2;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform float constant;
uniform float linear;
uniform float quadratic;

in vec2 v_TexCoord;
in vec3 Normal;
in vec3 FragPos;

void main()
{
  float ambientStrength = 0.1;
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

  float distance    = length(lightPos - FragPos);
  float attenuation = 1.0 / (constant + linear * distance + 
      quadratic * (distance * distance));    
  ambient*=attenuation;
  diffuse*=attenuation;
  specular*=attenuation;

  vec4 texColor = texture(u_texture, v_TexCoord);
  vec4 texColor2 = texture(u_texture2, v_TexCoord);
  vec3 result = (ambient + diffuse) * vec3(texColor) + specular * vec3(texColor2);

  /* result = round(result*8)/8; */

  FragColor = vec4(result, 1.0);
}
