#include "object.h"
#include <GL/glew.h>
#include "shader.h"
#include <stdlib.h>

struct Object * CreateObject(struct VertexArray * vao, struct Material * material, float * model, float * view, float * projection)
{
    struct Object * newObject = malloc(sizeof(struct Object));
    newObject->material = material;
    newObject->vao = vao;
    newObject->model = model;
    newObject->view = view;
    newObject->projection = projection;

    return newObject;
}

void BindMVP(unsigned int id, float * model, float * view, float * projection)
{
    
}

void BindObject(struct Object * object)
{
    glBindVertexArray(object->vao->id);
    BindMaterial(object->material);
    glUniformMatrix4fv(glGetUniformLocation(object->material->id, "model"), 1, GL_FALSE, object->model);
    glUniformMatrix4fv(glGetUniformLocation(object->material->id, "view"), 1, GL_FALSE, object->view);
    glUniformMatrix4fv(glGetUniformLocation(object->material->id, "projection"), 1, GL_FALSE, object->projection);
}
