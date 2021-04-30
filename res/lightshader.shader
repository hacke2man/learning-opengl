#version 330 core

layout(location = 0) out vec4 fragcolor;

uniform vec3 lightColor;

void main(){
  fragcolor = vec4(lightColor, 1.0);
}
