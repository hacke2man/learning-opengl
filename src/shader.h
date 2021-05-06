#ifndef __SHADER_H__
#define __SHADER_H__

#ifdef __cplusplus
extern "C" {
#endif

  struct Material {
    unsigned int id;
    float ambient[3];
    float diffuse[3];
    float specular[3];
    float shininess;
  };

  unsigned int CompileShader(unsigned int type, const char * source);
  struct Material * CreateMaterial(const char * vertexShader, const char * fragmentShader);

  void BindMaterial(struct Material * material);

  void AddUniform3fv(struct Material * material, char * uniformName, float * uniformData);

#ifdef __cplusplus
}
#endif

#endif
