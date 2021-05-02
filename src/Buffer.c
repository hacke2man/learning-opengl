#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include "Buffer.h"

struct VertexArray * CreateVertexArray(unsigned int count) {
    struct VertexArray * vertexArray = malloc(sizeof(struct VertexArray));
    vertexArray->attribPointer = malloc(sizeof(struct AttribPointer));
    vertexArray->attribPointer->count = count;
    vertexArray->attribPointer->nextPointer = NULL;
    vertexArray->pointerCount = 1;
    glGenVertexArrays(1, &vertexArray->id);
    glBindVertexArray(vertexArray->id);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, count, GL_FLOAT, GL_FALSE, count * sizeof(float), 0);
    return vertexArray;
}

void AddAttribPointer(struct VertexArray * vertexArray, unsigned int count) {
    struct AttribPointer * ap = vertexArray->attribPointer;
    int stride = 0;
    for(int i = 0; i < vertexArray->pointerCount; i++)
    {
        stride += ap->count * sizeof(float);
        if(ap->nextPointer != NULL)
            ap = ap->nextPointer;
    }
    stride += count * sizeof(float);


    ap = vertexArray->attribPointer;
    int offset = 0;
    int i;
    for(i = 0; i < vertexArray->pointerCount; i++)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, ap->count, GL_FLOAT, GL_FALSE, stride, (const void *)offset);
        offset += ap->count * sizeof(float);
        if(ap->nextPointer != NULL)
            ap = ap->nextPointer;
    }
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, count, GL_FLOAT, GL_FALSE, stride, (const void *)offset);

    struct AttribPointer * newPointer = malloc(sizeof(struct AttribPointer));
    newPointer->count = count;
    ap->nextPointer = newPointer;
    vertexArray->pointerCount++;
}

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
