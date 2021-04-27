#ifndef __RENDER_H__
#define __RENDER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Buffer.h"

  void Draw(struct IndexBuffer * indexBuffer, unsigned int vertexArray, unsigned int program);

#ifdef __cplusplus
}
#endif


#endif
