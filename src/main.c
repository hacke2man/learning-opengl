#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <limits.h>
#include <math.h>

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
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
vec3 charpos;
int forward = 0;
int backword = 0;
int leftword = 0;
int rightword = 0;
float mousex = -M_PI/2;
float mousey;


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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, &key_callback);
    glfwSetWindowSizeCallback(window, &window_size_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glewInit();
    glDebugMessageCallback(&DebugCallback, NULL);
    glEnable(GL_DEPTH_TEST);
    /* glEnable(GL_CULL_FACE); */
    /* glCullFace(GL_BACK); */
    /* glFrontFace(GL_CCW); */

    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);


    printf("%s\n", glGetString(GL_VERSION));

    /* float vertices[] = { */
    /*     -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,//front: bottom left */
    /*      0.5f, -0.5f,  0.5f, 1.0f, 0.0f,//bottom right */
    /*      0.5f,  0.5f,  0.5f, 1.0f, 1.0f,//top right */
    /*     -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,//top left */
    /*     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,//back: bottom left */
    /*      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,//bottom right */
    /*      0.5f,  0.5f, -0.5f, 1.0f, 1.0f,//top right */
    /*     -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,//top left */
    /* }; */

    /* unsigned int indices[] = { */
    /*     0, 3, 2,//front */
    /*     2, 1, 0, */

    /*     4, 7, 6,//back */
    /*     6, 5, 4, */

    /*     2, 6, 7,//top */
    /*     7, 3, 2, */

    /*     4, 0, 1,//bottom */
    /*     1, 5, 4, */

    /*     1, 2, 6, */
    /*     6, 5, 1, */

    /*     4, 7, 3, */
    /*     3, 0, 4 */
    /* }; */
    float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
    vec3 cubePositions[] = {
        { 0.0f,  0.0f,  0.0f}, 
        { 2.0f,  5.0f, -15.0f}, 
        {-1.5f, -2.2f, -2.5f},  
        {-3.8f, -2.0f, -12.3f},  
        { 2.4f, -0.4f, -3.5f},  
        {-1.7f,  3.0f, -7.5f},  
        { 1.3f, -2.0f, -2.5f},  
        { 1.5f,  2.0f, -2.5f}, 
        { 1.5f,  0.2f, -1.5f}, 
        {-1.3f,  1.0f, -1.5f}  
    };
    /* glEnable(GL_BLEND); */
    /* glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); */

    /* unsigned int vao; */
    /* glGenVertexArrays(1, &vao); */
    /* glBindVertexArray(vao); */

    struct VertexBuffer * vb = CreateVertexBuffer(sizeof(vertices), vertices);

    struct VertexArray * vao = CreateVertexArray(3);
    AddAttribPointer(vao, 3);
    AddAttribPointer(vao, 2);

    /* struct IndexBuffer * ibo = CreateIndexBuffer(36, indices); */

    unsigned int sourceVao;
    glGenVertexArrays(1, &sourceVao);
    glBindVertexArray(sourceVao);

    glBindBuffer(GL_ARRAY_BUFFER, vb->id);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);


    char * vertexShader = FileToString("/home/liam/dev/learning-opengl/res/vertex.shader");
    char * fragmentShader = FileToString("/home/liam/dev/learning-opengl/res/fragment.shader");
    char * lightshader = FileToString("/home/liam/dev/learning-opengl/res/lightshader.shader");
    unsigned int shader = CreateShader( vertexShader, fragmentShader);
    unsigned int lightsh = CreateShader( vertexShader, lightshader);

    mat4 projection; //glm_ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 100.0f, projection);
    glm_perspective(glm_rad(90.0f), (float)width/(float)height, 0.1f, 100.0f, projection);

    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);
    /* glUniform1i(glGetUniformLocation(shader, "u_texture"), 0); */
    glUniform1i(glGetUniformLocation(shader, "u_texture2"), 1);

    struct Texture * texture = CreateTexture("/home/liam/dev/learning-opengl/img/container2_specular.png");
    struct Texture * tex2 = CreateTexture("/home/liam/dev/learning-opengl/img/container2.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex2->id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    float offset = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float camdirz = sin(mousex) * cos(mousey);
        float camdirx = cos(mousex) * cos(mousey);
        float camdiry =0 - sin(mousey);

        vec3 eye = {charpos[0], charpos[1], charpos[2] + 3.0f};
        vec3 direction = {camdirx, camdiry, camdirz};
        vec3 up = {0.0, 1.0, 0.0};

        vec3 movedir;
        glm_vec3_divs(direction, 40, movedir);
        if(forward)
        {
            glm_vec3_add(charpos, movedir, charpos);
        } else if(backword) {
            glm_vec3_sub(charpos, movedir, charpos);
        }else if (leftword) {
            glm_vec3_rotate(movedir, glm_rad(90.0f), up);
            glm_vec3_divs(movedir, cos(mousey), movedir);
            movedir[1] = 0;
            glm_vec3_add(charpos, movedir, charpos);
        }else if(rightword) {
            glm_vec3_rotate(movedir, glm_rad(90.0f), up);
            glm_vec3_divs(movedir, cos(mousey), movedir);
            movedir[1] = 0;
            glm_vec3_sub(charpos, movedir, charpos);
        }

        glm_vec3_add(eye, direction, direction);

        mat4 model; glm_mat4_identity(model);
        offset += 0.0f; // 0.1f;
        vec3 axis = {1.0f, 0.3f, 0.5f};
        glm_rotate(model, glm_rad(offset), axis);
        mat4 view; glm_mat4_identity(view);
        glm_lookat(eye, direction, up, view);

        vec3 lightColor = {1.0f,1.0f,1.0f};
        /* vec3 lightColor = {245.0f/255.0f,212.0f/255.0f,0.0f}; */
        /* vec3 lightColor = {0.3f,0.8f,0.8f}; */
        vec3 objectColor = {1.0f, 0.5f, 0.31f};
        vec4 transiflup = { 1.2f, 1.0f, 2.0f};
        glm_vec3_rotate(transiflup, glm_rad(-offset * 10), up);
        /* glm_vec3_scale(transiflup, 5, transiflup); */

        glUseProgram(shader);
        glBindVertexArray(vao->id);
        glUniform3fv(glGetUniformLocation(shader, "lightColor"), 1, &lightColor[0]);
        glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, &eye[0]);
        glUniform3fv(glGetUniformLocation(shader, "objectColor"), 1, &objectColor[0]);
        glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, &transiflup[0]);
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);

        /* for(unsigned int i = 0; i < 10; i++) */
        /* { */
        /*     glm_mat4_identity(model); */
        /*     glm_translate(model, cubePositions[i]); */
        /*     float angle = 20.0f * i; */ 
        /*     glm_rotate(model, glm_rad(angle + offset), axis); */

        /*     glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]); */
        /*     glDrawArrays(GL_TRIANGLES, 0, 36); */
        /* } */
        /* glDrawElements(GL_TRIANGLES, ibo->count, GL_UNSIGNED_INT, NULL); *1/ */
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glUseProgram(lightsh);
        glUniform3fv(glGetUniformLocation(lightsh, "lightColor"), 1, &lightColor[0]);
        glUniformMatrix4fv(glGetUniformLocation(lightsh, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightsh, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightsh, "projection"), 1, GL_FALSE, &projection[0][0]);

        glm_translate_make(model, transiflup);
        vec3 a = {0.3f, 0.3f, 0.3f};
        glm_scale(model, a);
        glUniformMatrix4fv(glGetUniformLocation(lightsh, "model"), 1, GL_FALSE, &model[0][0]);
        /* glDrawElements(GL_TRIANGLES, ibo->count, GL_UNSIGNED_INT, NULL); */
        glBindVertexArray(sourceVao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glDeleteProgram(lightsh);
    glfwTerminate();
    return 0;
}
void window_size_callback(GLFWwindow * window, int width, int height){
    glViewport(0, 0, width, height);
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
    float moveLength = 1.0f;
    switch (key) {
        case GLFW_KEY_H:
            if(action == GLFW_PRESS) charpos[0] -= moveLength;
            break;
        case GLFW_KEY_L:
            if(action == GLFW_PRESS) charpos[0] += moveLength;
            break;
        case GLFW_KEY_J:
            if(action == GLFW_PRESS) charpos[2] += moveLength;
            break;
        case GLFW_KEY_K:
            if(action == GLFW_PRESS) charpos[2] -= moveLength;
            break;
        case GLFW_KEY_W:
            if(action == GLFW_PRESS || action == GLFW_REPEAT) forward = true;
            else forward = false;
            break;
        case GLFW_KEY_S:
            if(action == GLFW_PRESS || action == GLFW_REPEAT) backword = true;
            else backword = false;
            break;
        case GLFW_KEY_A:
            if(action == GLFW_PRESS || action == GLFW_REPEAT) leftword = true;
            else leftword = false;
            break;
        case GLFW_KEY_D:
            if(action == GLFW_PRESS || action == GLFW_REPEAT) rightword = true;
            else rightword = false;
            break;
        default:
            break;
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, (float)width/2, (float)height/2);

    mousex+=xpos/(float)width-0.5f;

    if((mousey +(ypos/height -0.5f)/3) < -3.14/2){
        mousey = -3.14/2;
    } else if((mousey +(ypos/height -0.5f)/3) > 3.14/2){
        mousey = 3.14/2;
    } else {
        mousey+= (ypos/height -0.5f)/3;
    }
}
