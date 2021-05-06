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
void calcView(mat4 * view, vec3 * direction);
void move();
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
float charpos[3] = {0, 0, 3.0};
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
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

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

    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);

    printf("%s\n", glGetString(GL_VERSION));

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

    struct VertexBuffer * vb = CreateVertexBuffer(vertices, sizeof(vertices), 8 * sizeof(float));
    struct VertexArray * vao = CreateVertexArray(vb);
    AddAttribPointer(vao, 3);
    AddAttribPointer(vao, 3);
    AddAttribPointer(vao, 2);

    struct VertexArray * sourceVao = CreateVertexArray(vb);
    AddAttribPointer(sourceVao, 3);

    char * vertexShader = FileToString("res/vert.vs");
    char * fragmentShader = FileToString("res/object.fs");
    char * lightshader = FileToString("res/light.fs");
    struct Material * box = CreateMaterial(vertexShader, fragmentShader);
    struct Material * light = CreateMaterial(vertexShader, lightshader);

    struct Texture * container_spec = CreateTexture("img/container2_specular.png");
    struct Texture * container = CreateTexture("img/container2.png");
    BindTexture(container_spec, GL_TEXTURE1);
    BindTexture(container, GL_TEXTURE0);

    vec3 direction;
    mat4 projection;
    glm_perspective(glm_rad(90.0f), (float)width/(float)height, 0.1f, 100.0f, projection);

    /* vec3 objectColor = {1.0f, 0.5f, 0.31f}; */
    vec3 objectColor = {0.3f,0.8f,0.8f};
    vec3 lightColor = {1.0f,1.0f,1.0f};
    /* vec3 lightColor = {245.0f/255.0f,212.0f/255.0f,0.0f}; */
    /* vec3 lightColor = {0.3f,0.8f,0.8f}; */
    vec3 lightPos = { 1.2f, 1.0f, 2.0f};




    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 model; glm_mat4_identity(model);
        mat4 view; glm_mat4_identity(view);

        calcView(&view, &direction);
        move(direction);

        glBindVertexArray(vao->id);
        BindMaterial(box);
        glUniform3fv(glGetUniformLocation(box->id, "lightPos"), 1, lightPos);
        glUniform3fv(glGetUniformLocation(box->id, "lightColor"), 1, lightColor);
        glUniform3fv(glGetUniformLocation(box->id, "objectColor"), 1, objectColor);
        glUniform3fv(glGetUniformLocation(box->id, "viewPos"), 1, charpos);
        glUniformMatrix4fv(glGetUniformLocation(box->id, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(box->id, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(box->id, "projection"), 1, GL_FALSE, &projection[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glm_translate_make(model, lightPos);
        vec3 resizer = {0.3f, 0.3f, 0.3f};
        glm_scale(model, resizer);

        glBindVertexArray(sourceVao->id);
        BindMaterial(light);
        glUniform3fv(glGetUniformLocation(light->id, "lightColor"), 1, &lightColor[0]);
        glUniformMatrix4fv(glGetUniformLocation(light->id, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(light->id, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(light->id, "projection"), 1, GL_FALSE, &projection[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(box->id);
    glDeleteProgram(light->id);
    glfwTerminate();
    return 0;
}

void calcView(mat4 * view, vec3 * direction)
{
    vec3 up = {0.0, 1.0, 0.0};
    vec3 center = {0.0f,0.0f,0.0f};

    vec3 newDir = {
        cos(mousex) * cos(mousey),
        -sin(mousey),
        sin(mousex) * cos(mousey)
    };

    glm_vec3_copy(newDir, *direction);

    glm_vec3_add(charpos, newDir, center);
    glm_lookat(charpos, center, up, *view);
}

void move(float direction[3])
{
    float movedir[3] = {0.0f,0.0f,0.0f};
    float up[3] = {0.0f,1.0f,0.0f};
    if(forward && backword){}
    else if(forward)
    {
        glm_vec3_add(direction, movedir, movedir);
    }else if(backword) {
        glm_vec3_add(direction, movedir, movedir);
        glm_vec3_scale(movedir, -1, movedir);
    }

    float strafeDir[3];
    glm_vec3_copy(direction, strafeDir);
    if(leftword && rightword){}
    else if (leftword) 
    {
        glm_vec3_rotate(strafeDir, glm_rad(90.0f), up);
        glm_vec3_divs(strafeDir, cos(mousey), strafeDir);
        strafeDir[1] = 0;
    }
    else if(rightword) 
    {
        glm_vec3_rotate(strafeDir, glm_rad(270.0f), up);
        glm_vec3_divs(strafeDir, cos(mousey), strafeDir);
        strafeDir[1] = 0;
    }

    if(leftword || rightword) glm_vec3_add(movedir, strafeDir, movedir);

    glm_vec3_normalize(movedir);
    glm_vec3_divs(movedir, 40, movedir);
    glm_vec3_add(movedir, charpos, charpos);
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
    switch (key) {
        case GLFW_KEY_W:
            if(action == GLFW_PRESS) forward = true;
            else if(action == GLFW_RELEASE) forward = false;
            break;
        case GLFW_KEY_S:
            if(action == GLFW_PRESS) backword = true;
            else if(action == GLFW_RELEASE) backword = false;
            break;
        case GLFW_KEY_A:
            if(action == GLFW_PRESS) leftword = true;
            else if(action == GLFW_RELEASE) leftword = false;
            break;
        case GLFW_KEY_D:
            if(action == GLFW_PRESS) rightword = true;
            else if(action == GLFW_RELEASE) rightword = false;
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
