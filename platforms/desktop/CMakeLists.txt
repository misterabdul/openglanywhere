cmake_minimum_required(VERSION 3.5)

project(OpenGLAnywhereDesktop)

add_definitions(-D__PLATFORM_DESKTOP__)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

set(OUTPUT openglanywhere)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK
    REQUIRED gtk4)
pkg_check_modules(GLM
    REQUIRED cglm)

set(LFLAGS "${LFLAGS} -lm")

add_executable(${OUTPUT}
    src/main.c
    src/glad.c
    ../../src/res.c
    ../../src/shader.c
    ../../src/stb_image.c
    ../../src/renderer.c)

set_target_properties(${OUTPUT}
    PROPERTIES LINK_FLAGS ${LFLAGS})

target_include_directories(${OUTPUT}
    PRIVATE ${GTK_INCLUDE_DIRS})
target_link_directories(${OUTPUT}
    PRIVATE ${GTK_LIBRARY_DIRS})
target_link_libraries(${OUTPUT}
    PRIVATE ${GTK_LIBRARIES})

target_include_directories(${OUTPUT}
    PRIVATE ${GLM_INCLUDE_DIRS})
target_link_directories(${OUTPUT}
    PRIVATE ${GLM_LIBRARY_DIRS})
target_link_libraries(${OUTPUT}
    PRIVATE ${GLM_LIBRARIES})

target_include_directories(${OUTPUT}
    PRIVATE ../../inc)
