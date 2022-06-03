#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#ifdef __PLATFORM_ANDROID__

#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "OpenGL Anywhere"
#endif

#define Console__eprintf(...) \
  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define Console__printf(...) \
  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#else

#include <stdio.h>

#define Console__eprintf(...) fprintf(stderr, __VA_ARGS__)
#define Console__printf(...) printf(__VA_ARGS__)

#endif

#endif
