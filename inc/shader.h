#ifndef __SHADER_H__
#define __SHADER_H__

/**
 * @brief Main shader data struct.
 */
typedef struct __shader_t {
  int id;
} * Shader;

/**
 * @brief Create new shader instance.
 *
 * @param[in]  vertexShader         Vertex shader source code.
 * @param[in]  vertexShaderLength   Vertex shader source code length.
 * @param[in]  fragmentShader       Fragment shader source code.
 * @param[in]  fragmentShaderLength Fragment shader source code length.
 * @return                          Shader instance.
 */
Shader Shader__new(const unsigned char* vertexShader,
                   const unsigned int* vertexShaderLenght,
                   const unsigned char* fragmentShader,
                   const unsigned int* fragmentShaderLength);

/**
 * @brief Use the shader instance's program.
 *
 * @param[in] shader The shader instance.
 */
void Shader__useProgram(const Shader shader);

/**
 * @brief Delete the shader instance's program.
 *
 * @param[in] shader The shader instance.
 */
void Shader__deleteProgram(const Shader shader);

/**
 * @brief Set boolean value for shader.
 *
 * @param[in] shader The shader instance.
 * @param[in] name   The name for the value.
 * @param[in] value  The value to be set.
 */
void Shader__setBool(const Shader shader, const char* name, int value);

/**
 * @brief Set integer value for shader.
 *
 * @param[in] shader The shader instance.
 * @param[in] name   The name for the value.
 * @param[in] value  The value to be set.
 */
void Shader__setInt(const Shader shader, const char* name, int value);

/**
 * @brief Set float value for shader.
 *
 * @param[in] shader The shader instance.
 * @param[in] name   The name for the value.
 * @param[in] value  The value to be set.
 */
void Shader__setFloat(const Shader shader, const char* name, float value);

/**
 * @brief Set 3D float vector value for shader.
 *
 * @param[in] shader The shader instance.
 * @param[in] name   The name for the value.
 * @param[in] x      The x value to be set.
 * @param[in] y      The y value to be set.
 * @param[in] z      The z value to be set.
 */
void Shader__set3Float(const Shader shader,
                       const char* name,
                       const float x,
                       const float y,
                       const float z);

/**
 * @brief Set 4x4 matrix value for shader.
 *
 * @param[in] shader The shader instance.
 * @param[in] name   The name for the value.
 * @param[in] value  The 4x4 matrix value to be set.
 */
void Shader__setMat4(const Shader shader, const char* name, const float* value);

/**
 * @brief Free the shader instance.
 *
 * @param[in] shader The shader instance.
 */
void Shader__free(Shader shader);

#endif
