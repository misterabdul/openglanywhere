#include <console.h>
#include <shader.h>

#include <stdlib.h>

#ifdef __PLATFORM_BROWSER__
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#elif __PLATFORM_ANDROID__
#include <GLES3/gl3.h>
#else
#include "../platforms/desktop/src/glad.h"
#endif

Shader Shader__new(const unsigned char* vertexShaderSource,
                   const unsigned int* vertexShaderSourceLength,
                   const unsigned char* fragmentShaderSource,
                   const unsigned int* fragmentShaderSourceLength) {
  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
#ifdef __PLATFORM_BROWSER__
  glShaderSource(vertexShader, 1, (const GLchar* const*)(&vertexShaderSource),
                 (const GLint*)vertexShaderSourceLength);
#else
  glShaderSource(vertexShader, 1, (const GLchar* const*)(&vertexShaderSource),
                 (const GLuint*)vertexShaderSourceLength);
#endif
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    Console__eprintf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
#ifdef __PLATFORM_BROWSER__
  glShaderSource(fragmentShader, 1,
                 (const GLchar* const*)(&fragmentShaderSource),
                 (const GLint*)fragmentShaderSourceLength);
#else
  glShaderSource(fragmentShader, 1,
                 (const GLchar* const*)(&fragmentShaderSource),
                 (const GLuint*)fragmentShaderSourceLength);
#endif
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    Console__eprintf("%s\n", fragmentShaderSource);
    Console__eprintf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
  }
  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    Console__eprintf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  Shader shader = malloc(sizeof(struct __shader_t));
  shader->id = shaderProgram;

  return shader;
}

void Shader__useProgram(const Shader shader) {
  glUseProgram(shader->id);
}

void Shader__deleteProgram(const Shader shader) {
  glDeleteProgram(shader->id);
}

void Shader__setBool(const Shader shader, const char* name, int value) {
  glUniform1i(glGetUniformLocation(shader->id, name), value);
}

void Shader__setInt(const Shader shader, const char* name, int value) {
  glUniform1i(glGetUniformLocation(shader->id, name), value);
}

void Shader__setFloat(const Shader shader, const char* name, float value) {
  glUniform1f(glGetUniformLocation(shader->id, name), value);
}

void Shader__set3Float(const Shader shader,
                       const char* name,
                       float x,
                       float y,
                       float z) {
  glUniform3f(glGetUniformLocation(shader->id, name), x, y, z);
}

void Shader__setMat4(const Shader shader,
                     const char* name,
                     const float* value) {
  glUniformMatrix4fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE,
                     value);
}

void Shader__free(Shader this) {
  free(this);
}
