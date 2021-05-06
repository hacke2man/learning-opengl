#include "shader.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

struct Material * CreateMaterial(const char * vertexShader, const char * fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    struct Material * newMaterial = malloc(sizeof(struct Material));
    newMaterial->id = program;

    return newMaterial;
}

void Bind3fv(struct Material * material, char * uniformName, float uniformData[]){
    glUniform3fv(glGetUniformLocation(material->id, uniformName), 1, &uniformData[0]);
}

void BindMaterial(struct Material * material)
{
    glUseProgram(material->id);
}

unsigned int CompileShader(unsigned int type, const char * source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char * message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        printf("%s %s\n", type == GL_VERTEX_SHADER ? "vertex\n" : "fragment\n" , message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}
