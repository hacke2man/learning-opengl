#ifndef __BUFFER_H__
#define __BUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif

  void CreateVertexBuffer(unsigned int * buffer, unsigned int size, float * data);

  void CreateIndexBuffer(unsigned int * buffer, unsigned int count, unsigned int * data);

#ifdef __cplusplus
}
#endif


#endif
