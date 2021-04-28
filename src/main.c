#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <limits.h>

#include "deps/cglm/include/cglm/affine.h"
#include "deps/cglm/include/cglm/cglm.h"
#include "deps/cglm/include/cglm/cam.h"

#include "deps/cglm/include/cglm/mat4.h"
#include "deps/cglm/include/cglm/project.h"
#include "deps/cglm/include/cglm/util.h"
#include "deps/cglm/include/cglm/vec3.h"
#include "fileToString.h"
#include "Buffer.h"
#include "shader.h"
#include "Render.h"
#include "Texture.h"

void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
void window_size_callback(GLFWwindow * window, int width, int height);
int test = 0;
int resized = 0;
int charPosx = 0;
int charPosy = 0;

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

    int width, height, xpos, ypos;
    GLFWmonitor * primary = glfwGetPrimaryMonitor();
    /* glfwGetMonitorWorkarea(primary, &xpos, &ypos, &width, &height); */
    /* const GLFWvidmode * mode = glfwGetVideoMode(primary); */
    /* glfwWindowHint(GLFW_RED_BITS, mode->redBits); */
    /* glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits); */
    /* glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits); */
    /* glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate); */
    /* glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE); */
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    /* window = glfwCreateWindow(width, height, "Hello World", NULL, NULL); */
    /* window = glfwCreateWindow(width, height, "Hello World", primary , NULL); */
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, &key_callback);
    glfwSetWindowSizeCallback(window, &window_size_callback);
    glewInit();
    glDebugMessageCallback(&DebugCallback, NULL);
    glEnable(GL_DEPTH_TEST);
    /* glEnable(GL_CULL_FACE); */
    /* glCullFace(GL_BACK); */
    /* glFrontFace(GL_CCW); */

    glfwGetWindowSize(window, &width, &height);
    printf("%d %d\n",width, height);
    glViewport(0, 0, width, height);


    printf("%s\n", glGetString(GL_VERSION));

    /* float positions[] = { */
    /*     //pos              //tex coords */
    /*     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, */
    /*     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, */
    /*    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, */
    /*    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, */
    /* }; */
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    /* unsigned int indices[] = { */
    /*     0, 1, 3, */
    /*     1, 2, 3 */
    /* }; */

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    struct VertexBuffer * vb = CreateVertexBuffer(sizeof(vertices), vertices);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (const void *) (3 * sizeof(float)));

    /* struct IndexBuffer * ibo = CreateIndexBuffer(6, indices); */

    char * vertexShader = FileToString("/home/liam/dev/learning-opengl/res/vertex.shader");
    char * fragmentShader = FileToString("/home/liam/dev/learning-opengl/res/fragment.shader");
    unsigned int shader = CreateShader( vertexShader, fragmentShader);

    glUseProgram(shader);

    mat4 model; glm_mat4_identity(model);
    vec4 axis = {1.0f, 1.0f, 0.0f}; 
    vec4 axis1 = {1.0f, 1.0f, 0.0f}; 
    glm_rotate(model, glm_rad(-55.0f), axis);

    mat4 view; glm_mat4_identity(view);
    vec4 translator = {0.0f,0.0f,-3.0f};
    glm_translate(view, translator);

    mat4 projection;// glm_ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f, projection);
    glm_perspective(glm_rad(45.0f), (float)width/(float)height, 0.1f, 100.0f, projection);

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);
    glUniform1i(glGetUniformLocation(shader, "u_texture"), 0);

    struct Texture * texture = CreateTexture("/home/liam/dev/learning-opengl/img/link.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm_rotate(model, glm_rad(0.5f), axis);
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);

        if(resized){
            glfwGetWindowSize(window, &width, &height);
            resized = 0;
        }

        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        /* Draw(ibo, vao, shader); */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
void window_size_callback(GLFWwindow * window, int width, int height){
    glViewport(0, 0, width, height);
    resized = 1;
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

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    switch (key) {
        case GLFW_KEY_H:
            if(action == GLFW_PRESS) charPosx -= 100;
            break;
        case GLFW_KEY_L:
            if(action == GLFW_PRESS) charPosx += 100;
            break;
        case GLFW_KEY_J:
            if(action == GLFW_PRESS) charPosy -= 100;
            break;
        case GLFW_KEY_K:
            if(action == GLFW_PRESS) charPosy += 100;
            break;
        default:
            break;
    }
    if(key == GLFW_KEY_J && action == GLFW_PRESS)
        test = !test;
}
