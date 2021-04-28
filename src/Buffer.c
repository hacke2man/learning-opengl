#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include "Buffer.h"

struct VertexBuffer * CreateVertexBuffer(unsigned int size, float data[])
{
<<<<<<< HEAD
    struct VertexBuffer * vertexBuffer = malloc(sizeof(struct VertexBuffer));
    vertexBuffer->size = size;
    vertexBuffer->data = data;
    glGenBuffers(1, &vertexBuffer->id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
    return vertexBuffer;
=======
    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
>>>>>>> f1793e6864c06aa969201bf09d90f6c39ae6df16
}

struct IndexBuffer * CreateIndexBuffer(unsigned int count, unsigned int indices[])
{
    struct IndexBuffer * indexBuffer = malloc(sizeof(struct VertexBuffer));
    indexBuffer->count = count;
    indexBuffer->indices = indices;
    glGenBuffers(1, &indexBuffer->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STREAM_DRAW);
    return indexBuffer;
}
