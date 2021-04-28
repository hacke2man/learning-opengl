#include "Render.h"
#include <GL/glew.h>

void Draw(struct IndexBuffer * indexBuffer, unsigned int vertexArray, unsigned int program)
{
    glUseProgram(program);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->id);

    glDrawElements(GL_TRIANGLES, indexBuffer->count, GL_UNSIGNED_INT, NULL);
}
