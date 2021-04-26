#include <GL/glew.h>
#include "Buffer.h"

void CreateVertexBuffer(unsigned int * buffer, unsigned int size, float * data)
{
    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
}

void CreateIndexBuffer(unsigned int * ibo, unsigned int count, unsigned int * data)
{
    glGenBuffers(1, ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}
