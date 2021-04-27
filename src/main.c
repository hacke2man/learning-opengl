#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

#include "fileToString.h"
#include "Buffer.h"
#include "shader.h"
#include "Render.h"

void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    glDebugMessageCallback(&DebugCallback, NULL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


    printf("%s\n", glGetString(GL_VERSION));

    float positions[] = {
        0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 3,
        3, 2, 0,
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    struct VertexBuffer * vb = CreateVertexBuffer(sizeof(positions), positions);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_TRUE, 4*sizeof(float), 0);

    struct IndexBuffer * ibo = CreateIndexBuffer(6, indices);

    char * vertexShader = FileToString("/home/liam/dev/learning-opengl/res/vertex.shader");
    char * fragmentShader = FileToString("/home/liam/dev/learning-opengl/res/fragment.shader");
    unsigned int shader = CreateShader( vertexShader, fragmentShader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        Draw(ibo, vao, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}

void DebugCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar *message,
            const void *userParam){
    printf("type: %x ", type);
    printf("id: %d ", id);
    printf("severity: %x\n", severity);
    printf("%s\n", message);
    printf("\n");

    if(severity == GL_DEBUG_SEVERITY_HIGH){
        exit(2);
    }
}
