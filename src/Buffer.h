#ifndef __BUFFER_H__
#define __BUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif

  struct IndexBuffer {
    unsigned int id;
    unsigned int * indices;
    unsigned int count;
  };

  struct VertexBuffer {
    unsigned int id;
    float * data;
    unsigned int size;
    unsigned int stride;
  };

  struct VertexArray {
    unsigned int id;
    unsigned long offset;
    unsigned int pointerCount;
    struct VertexBuffer * data;
  };

  struct VertexArray * CreateVertexArray(struct VertexBuffer * data);
  void AddAttribPointer(struct VertexArray * vertexArray, unsigned int count);

  struct VertexBuffer * CreateVertexBuffer(float data[], unsigned int size, unsigned int stride);

  struct IndexBuffer * CreateIndexBuffer(unsigned int count, unsigned int * indices);

#ifdef __cplusplus
}
#endif


#endif
