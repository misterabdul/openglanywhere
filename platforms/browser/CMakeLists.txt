cmake_minimum_required(VERSION 3.5)

project(OpenGLAnywhereBrowser)

add_definitions(-D__PLATFORM_BROWSER__)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_EXECUTABLE_SUFFIX .html)

set(OUTPUT openglanywhere)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW
    REQUIRED glfw3)

include(FetchContent)
FetchContent_Declare(
        cglm
        GIT_REPOSITORY https://github.com/recp/cglm.git
        GIT_TAG        v0.8.5)
if(NOT cglm_POPULATED)
    FetchContent_Populate(cglm)
    add_subdirectory(${cglm_SOURCE_DIR} ${cglm_BINARY_DIR})
endif()

set(LFLAGS "${LFLAGS} -sMIN_WEBGL_VERSION=3 -sMAX_WEBGL_VERSION=3 -sFULL_ES3=1 -sWASM=1 -sUSE_GLFW=3 --emrun")
set(LFLAGS "${LFLAGS} -lm")

add_executable(${OUTPUT}
    src/main.c
    ../../src/res.c
    ../../src/shader.c
    ../../src/stb_image.c
    ../../src/renderer.c)

set_target_properties(${OUTPUT}
    PROPERTIES LINK_FLAGS ${LFLAGS})

target_include_directories(${OUTPUT}
    PRIVATE ${GLFW_INCLUDE_DIRS})

target_include_directories(${OUTPUT}
    PRIVATE ../../inc
    PRIVATE ${cglm_SOURCE_DIR}/include)
