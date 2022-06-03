#include <gtk/gtk.h>
#include <stdlib.h>

#include "glad.h"
#include "main.h"

#include <renderer.h>

MainData mainData;

/**
 * @brief Handler for on realize signal on gtk glarea.
 *
 * @param[in] area The gtk glarea instance.
 */
static void glArea__onRealize(GtkGLArea* area) {
  gtk_gl_area_make_current(area);

  GdkGLContext* context;
  context = gtk_gl_area_get_context(GTK_GL_AREA(area));

  gladLoadGL();

  Renderer__init(mainData->renderer);
}

/**
 * @brief Handler for on render signal on gtk glarea.
 *
 * @param[in] area The gtk glarea instance.
 * @return Handler result.
 */
static gboolean glArea__onRender(GtkGLArea* area, GdkGLContext* context) {
  Renderer__render(mainData->renderer);

  return TRUE;
}

/**
 * @brief Handler for tick callback on gtk glarea.
 *
 * @param[in] area The gtk glarea instance.
 * @param[in] frameClock  The gdk frame clock instance.
 * @param[in] data Custom user data.
 * @return Handler result.
 */
static gboolean glArea__onTick(GtkWidget* area,
                               GdkFrameClock* frameClock,
                               gpointer data) {
  Renderer__render(mainData->renderer);
  gtk_widget_queue_draw(area);

  return G_SOURCE_CONTINUE;
}

/**
 * @brief Handler for on unrealize signal on gtk glarea.
 *
 * @param[in] area The gtk glarea instance.
 */
static void glArea__onUnrealize(GtkGLArea* area) {
  gtk_gl_area_make_current(area);

  GdkGLContext* context;
  context = gtk_gl_area_get_context(GTK_GL_AREA(area));

  Renderer__kill(mainData->renderer);
}

/**
 * @brief Handler for activate signal on gtk application.
 *
 * @param[in] app  The gtk application instance.
 * @param[in] data Data.
 */
static void app__onActivate(GtkApplication* app, gpointer data) {
  GtkWidget* window;
  GtkWidget* glarea;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

  glarea = gtk_gl_area_new();
  gtk_gl_area_set_has_depth_buffer(GTK_GL_AREA(glarea), TRUE);
  g_signal_connect(GTK_GL_AREA(glarea), "realize",
                   G_CALLBACK(glArea__onRealize), NULL);
  g_signal_connect(GTK_GL_AREA(glarea), "render", G_CALLBACK(glArea__onRender),
                   NULL);
  g_signal_connect(GTK_GL_AREA(glarea), "unrealize",
                   G_CALLBACK(glArea__onUnrealize), NULL);
  gtk_widget_add_tick_callback(glarea, glArea__onTick, NULL, NULL);
  gtk_window_set_child(GTK_WINDOW(window), glarea);

  gtk_window_present(GTK_WINDOW(window));
}

/**
 * @brief Main function.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Program status.
 */
int main(int argc, char** argv) {
  mainData = malloc(sizeof(struct __main_data_t));
  mainData->app = gtk_application_new("moe.misterabdul.openglanywhere",
                                      G_APPLICATION_FLAGS_NONE);
  mainData->renderer = Renderer__new();

  g_signal_connect(mainData->app, "activate", G_CALLBACK(app__onActivate),
                   NULL);

  int status = g_application_run(G_APPLICATION(mainData->app), argc, argv);

  g_object_unref(mainData->app);
  Renderer__free(mainData->renderer);
  free(mainData);

  return status;
}
