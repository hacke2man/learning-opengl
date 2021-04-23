#ifndef __SHADER_H__
#define __SHADER_H__

#ifdef __cplusplus
extern "C" {
#endif

  unsigned int CompileShader(unsigned int type, const char * source);
  unsigned int CreateShader(const char * vertexShader, const char * fragmentShader);

#ifdef __cplusplus
}
#endif

#endif
