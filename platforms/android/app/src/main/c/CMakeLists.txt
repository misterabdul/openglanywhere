cmake_minimum_required(VERSION 3.5)

project(OpenGLAnywhereAndroid)

add_definitions(
    -D__PLATFORM_ANDROID__
    -DLOG_TAG="OpenGL Anywhere Android")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

set(OUTPUT openglanywhere)

include(FetchContent)
FetchContent_Declare(
    cglm
    GIT_REPOSITORY https://github.com/recp/cglm.git
    GIT_TAG        v0.8.5)
if(NOT cglm_POPULATED)
    FetchContent_Populate(cglm)
    add_subdirectory(${cglm_SOURCE_DIR} ${cglm_BINARY_DIR})
endif()

set(LFLAGS "${LFLAGS} -lm")

add_library(${OUTPUT}
    SHARED native-lib.c
    ../../../../../../src/res.c
    ../../../../../../src/shader.c
    ../../../../../../src/stb_image.c
    ../../../../../../src/renderer.c)

target_link_libraries(${OUTPUT}
    PRIVATE log
    PRIVATE EGL
    PRIVATE GLESv3)

target_include_directories(${OUTPUT}
    PRIVATE ../../../../../../inc
    PRIVATE ${cglm_SOURCE_DIR}/include)
