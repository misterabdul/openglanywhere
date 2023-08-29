cmake_minimum_required(VERSION 3.5)

project(OpenGLAnywhere
    VERSION 0.1
    DESCRIPTION "Example running OpenGL native C codes on desktop, browsers, & mobile apps."
    LANGUAGES C)

find_program(XXD xxd REQUIRED)
file(GLOB_RECURSE ress res/*)
file(WRITE src/res.c "/**\n")
file(APPEND src/res.c " * @brief This is a generated file.\n")
file(APPEND src/res.c " *        Do not add or include this file to the source control.\n")
file(APPEND src/res.c " */\n\n\n")
foreach(res ${ress})
    string(REGEX MATCH "(res/.+)$" filename ${res})
    execute_process(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND ${XXD} -i ${filename}
        OUTPUT_VARIABLE res_c)
    file(APPEND src/res.c "${res_c}")
endforeach()

if(EMSCRIPTEN)
add_subdirectory(platforms/browser)
else()
add_subdirectory(platforms/desktop)
endif()
