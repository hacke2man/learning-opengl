#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include "Buffer.h"

struct VertexArray * CreateVertexArray(struct VertexBuffer * data) {
    struct VertexArray * vertexArray = malloc(sizeof(struct VertexArray));
    vertexArray->data = data;
    vertexArray->pointerCount = 0;
    glGenVertexArrays(1, &vertexArray->id);
    glBindVertexArray(vertexArray->id);
    return vertexArray;
}

void AddAttribPointer(struct VertexArray * vertexArray, unsigned int count) {
    glBindVertexArray(vertexArray->id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArray->data->id);
    unsigned int stride = vertexArray->data->stride;
    glEnableVertexAttribArray(vertexArray->pointerCount);
    glVertexAttribPointer(vertexArray->pointerCount, count, GL_FLOAT, GL_FALSE, stride, (const void *) vertexArray->offset);

    vertexArray->offset += count * sizeof(float);
    vertexArray->pointerCount++;
}

struct VertexBuffer * CreateVertexBuffer(float data[], unsigned int size, unsigned int stride)
{
    struct VertexBuffer * vertexBuffer = malloc(sizeof(struct VertexBuffer));
    vertexBuffer->size = size;
    vertexBuffer->data = data;
    vertexBuffer->stride = stride;
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
