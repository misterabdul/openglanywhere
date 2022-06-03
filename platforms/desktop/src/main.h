#ifndef __MAIN_H__
#define __MAIN_H__

#include <gtk/gtk.h>

#include <renderer.h>

/**
 * @brief Structure for main program's data.
 */
typedef struct __main_data_t {
  GtkApplication* app;
  Renderer renderer;
} * MainData;

#endif
