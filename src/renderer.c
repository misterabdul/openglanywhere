#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <console.h>
#include <renderer.h>
#include <res.h>
#include <shader.h>
#include <stb_image.h>

#ifdef __PLATFORM_BROWSER__
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#endif

#ifdef __PLATFORM_DESKTOP__
#include "../platforms/desktop/src/glad.h"
#elif __PLATFORM_ANDROID__
#include <GLES3/gl3.h>
#else
#include <GL/gl.h>
#endif

typedef struct __private_t {
  struct __renderer_t renderer;
  Shader shader;
  unsigned int VBO;
  unsigned int VAO;
  unsigned int texture1;
  unsigned int texture2;
  float iRot;
} * Private;

#ifdef __PLATFORM_DESKTOP__
const unsigned char* vertexShaderSource = res_shaders_cube_vs;
const unsigned int* vertexShaderSourceLength = &res_shaders_cube_vs_len;
const unsigned char* fragmentShaderSource = res_shaders_cube_fs;
const unsigned int* fragmentShaderSourceLength = &res_shaders_cube_fs_len;
#else
const unsigned char* vertexShaderSource = res_shaders_cube_es_vs;
const unsigned int* vertexShaderSourceLength = &res_shaders_cube_es_vs_len;
const unsigned char* fragmentShaderSource = res_shaders_cube_es_fs;
const unsigned int* fragmentShaderSourceLength = &res_shaders_cube_es_fs_len;
#endif

Renderer Renderer__new(void) {
  Private renderer = malloc(sizeof(struct __private_t));
  renderer->shader = 0;
  renderer->VBO = 0;
  renderer->VAO = 0;
  renderer->texture1 = 0;
  renderer->texture2 = 0;
  renderer->iRot = 0.0f;

  return (Renderer)renderer;
}

void Renderer__init(const Renderer this) {
  Private _private = (Private)this;
  _private->shader =
      Shader__new(vertexShaderSource, vertexShaderSourceLength,
                  fragmentShaderSource, fragmentShaderSourceLength);

  // enable 3d depth testing by opengl
  glEnable(GL_DEPTH_TEST);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  glGenVertexArrays(1, &(_private->VAO));
  glGenBuffers(1, &(_private->VBO));
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(_private->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, _private->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(2);

  stbi_set_flip_vertically_on_load(0x1);

  // load and create a texture
  // -------------------------
  glGenTextures(1, &(_private->texture1));
  glBindTexture(GL_TEXTURE_2D,
                _private->texture1);  // all upcoming GL_TEXTURE_2D operations
                                      // now have effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  unsigned char* data = stbi_load_from_memory(res_images_container_jpg,
                                              res_images_container_jpg_len,
                                              &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    Console__eprintf("Failed to load texture\n");
  }
  stbi_image_free(data);

  // load and create second texture
  // -------------------------
  glGenTextures(1, &(_private->texture2));
  glBindTexture(GL_TEXTURE_2D,
                _private->texture2);  // all upcoming GL_TEXTURE_2D operations
                                      // now have effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  data = stbi_load_from_memory(res_images_awesomeface_png,
                               res_images_awesomeface_png_len, &width, &height,
                               &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    Console__eprintf("Failed to load texture\n");
  }
  stbi_image_free(data);

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

float Renderer__getAngleByTime(const Renderer this) {
  Private _this = (Private)this;
  time_t _now = time(NULL);
  float now = (_this->iRot++ / 50);
  // float now = (float)(_now % 100);
  return now * glm_rad(10.0f);
}

void Renderer__viewportChange(const Renderer this,
                              const int width,
                              const int height) {
  glViewport(0, 0, width, height);
}

void Renderer__render(const Renderer this) {
  Private _this = (Private)this;

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // bind Texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _this->texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, _this->texture2);

  // create the model, view, and projection matrix
  mat4 model;
  glm_mat4_identity(model);
  float angle = Renderer__getAngleByTime(this);
  glm_rotate(model, angle, (vec3){0.5f, 1.0f, 0.0f});
  mat4 view;
  glm_mat4_identity(view);
  glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});
  mat4 projection;
  glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection);

  // draw our first triangle
  Shader__useProgram(_this->shader);
  unsigned int modelLoc = glGetUniformLocation(_this->shader->id, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
  unsigned int viewLoc = glGetUniformLocation(_this->shader->id, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)view);
  unsigned int projectionLoc =
      glGetUniformLocation(_this->shader->id, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (const GLfloat*)projection);

  // render container
  glBindVertexArray(_this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer__kill(const Renderer this) {
  Private _this = (Private)this;

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &(_this->VAO));
  glDeleteBuffers(1, &(_this->VBO));
  Shader__deleteProgram(_this->shader);
}

void Renderer__free(const Renderer this) {
  Private _this = (Private)this;
  free(_this);
}
