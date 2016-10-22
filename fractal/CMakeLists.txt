cmake_minimum_required(VERSION 3.6)
project(fractal)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp DrawContext.cpp DrawContext.h utils.h)

set(CMAKE_VERBOSE_MAKEFILE ON)
add_executable(fractal ${SOURCE_FILES})

#target_include_directories(fractal ${OpenGL_INCLUDE_DIR})
target_link_libraries(fractal ${OPENGL_gl_LIBRARY} glfw GLEW)


