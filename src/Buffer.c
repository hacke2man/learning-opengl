#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include "Buffer.h"

struct VertexBuffer * CreateVertexBuffer(unsigned int size, float data[])
{
    struct VertexBuffer * vertexBuffer = malloc(sizeof(struct VertexBuffer));
    vertexBuffer->size = size;
    vertexBuffer->data = data;
    glGenBuffers(1, &vertexBuffer->id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
    return vertexBuffer;
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
