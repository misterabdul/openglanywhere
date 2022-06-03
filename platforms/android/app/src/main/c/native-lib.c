#include <jni.h>

#include <renderer.h>

JNIEXPORT jlong JNICALL
Java_moe_misterabdul_openglanywhere_opengl_OpenGlNativeLib_initialize(
    JNIEnv* env,
    jclass cls) {
  Renderer renderer = Renderer__new();

  return (jlong)renderer;
}

JNIEXPORT void JNICALL
Java_moe_misterabdul_openglanywhere_opengl_OpenGlNativeLib_deinitialize(
    JNIEnv* env,
    jclass cls,
    jlong renderer) {
  Renderer__free((Renderer)renderer);
}

JNIEXPORT void JNICALL
Java_moe_misterabdul_openglanywhere_opengl_OpenGlNativeLib_onSurfaceCreated(
    JNIEnv* env,
    jclass cls,
    jlong renderer) {
  Renderer__init((Renderer)renderer);
}

JNIEXPORT void JNICALL
Java_moe_misterabdul_openglanywhere_opengl_OpenGlNativeLib_onSurfaceChanged(
    JNIEnv* env,
    jclass cls,
    jlong renderer,
    jint width,
    jint height) {
  Renderer__viewportChange((Renderer)renderer, width, height);
}

JNIEXPORT void JNICALL
Java_moe_misterabdul_openglanywhere_opengl_OpenGlNativeLib_onDrawFrame(
    JNIEnv* env,
    jclass cls,
    jlong renderer) {
  Renderer__render((Renderer)renderer);
}

JNIEXPORT void JNICALL
Java_moe_misterabdul_openglanywhere_opengl_OpenGlNativeLib_onDestroy(
    JNIEnv* env,
    jclass cls,
    jlong renderer) {
  Renderer__kill((Renderer)renderer);
}
