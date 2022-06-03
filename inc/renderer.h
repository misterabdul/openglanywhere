#ifndef __RENDERER_H__
#define __RENDERER_H__

/**
 * @brief Main renderer struct.
 */
typedef struct __renderer_t {
} * Renderer;

/**
 * @brief Create new renderer instance.
 *
 * @return Renderer instance.
 */
Renderer Renderer__new(void);

/**
 * @brief Initialize renderer.
 *
 * @param[in] renderer The renderer instance.
 */
void Renderer__init(const Renderer renderer);

/**
 * @brief Do the rendering.
 *
 * @param[in] renderer The renderer instance.
 */
void Renderer__render(const Renderer renderer);

/**
 * @brief Handle viewport change.
 *
 * @param[in] renderer  The renderer instance.
 * @param[in] width     The new viewport width.
 * @param[in] height    The new viewport height.
 */
void Renderer__viewportChange(const Renderer renderer,
                              const int width,
                              const int height);

/**
 * @brief Free the renderer's initialized data.
 *
 * @param[in] renderer The renderer instance.
 */
void Renderer__kill(const Renderer renderer);

/**
 * @brief Free the renderer instance.
 *
 * @param[in] renderer The renderer instance.
 */
void Renderer__free(const Renderer renderer);

#endif
