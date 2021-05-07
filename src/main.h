#ifndef __MAIN_H__
#define __MAIN_H__
#ifdef __cplusplus
extern "C" {
#endif

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
#include "object.h"

GLFWwindow * SetupGLFW();
void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
void window_size_callback(GLFWwindow * window, int width, int height);
void calcView(mat4 * view, vec3 * direction);
void move();
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

#ifdef __cplusplus
}
#endif
#endif
