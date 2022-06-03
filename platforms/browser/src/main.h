#ifndef __MAIN_H__
#define __MAIN_H__

#include <GLFW/glfw3.h>

#include <renderer.h>

/**
 * @brief Structure for main program's data.
 */
typedef struct __main_data_t {
  GLFWwindow* window;
  Renderer renderer;
} * MainData;

#endif
