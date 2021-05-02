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
  };

  struct VertexArray {
    unsigned int id;
    unsigned int pointerCount;
    struct AttribPointer * attribPointer;
  };

  struct AttribPointer {
    unsigned int count;
    struct AttribPointer * nextPointer;
  };

  struct VertexArray * CreateVertexArray(unsigned int count);
  void AddAttribPointer(struct VertexArray * vertexArray, unsigned int count);

  struct VertexBuffer * CreateVertexBuffer(unsigned int size, float * data);

  struct IndexBuffer * CreateIndexBuffer(unsigned int count, unsigned int * indices);

#ifdef __cplusplus
}
#endif


#endif
