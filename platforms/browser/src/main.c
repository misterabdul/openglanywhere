#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <renderer.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

MainData mainData;

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  Renderer__viewportChange(mainData->renderer, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 0x1);
}

void mainLoop() {
  // input
  // -----
  processInput(mainData->window);

  Renderer__render(mainData->renderer);

  // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
  // etc.)
  // -------------------------------------------------------------------------------
  glfwSwapBuffers(mainData->window);
  glfwPollEvents();
}

int main() {
  mainData = malloc(sizeof(struct __main_data_t));

  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw window creation
  // --------------------
  mainData->window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLAnywhere", NULL, NULL);
  if (mainData->window == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(mainData->window);
  glfwSetFramebufferSizeCallback(mainData->window, framebufferSizeCallback);

  mainData->renderer = Renderer__new();

  Renderer__init(mainData->renderer);

  // render loop
  // -----------
  emscripten_set_main_loop(mainLoop, 0, 1);

  Renderer__kill(mainData->renderer);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();

  Renderer__free(mainData->renderer);
  free(mainData);

  return 0;
}
