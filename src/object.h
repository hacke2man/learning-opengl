#ifndef __OBJECT_H__
#define __OBJECT_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "shader.h"
#include "Buffer.h"

  struct Object {
    float * model;
    float * view;
    float * projection;

    struct Material * material;
    struct VertexArray * vao;
  };

  struct Object * CreateObject(struct VertexArray * vao, struct Material * material, float * model, float * view, float * projection);
  void BindMVP(unsigned int id, float * model, float * view, float * projection);
  void BindObject(struct Object * object);

#ifdef __cplusplus
}
#endif
#endif
