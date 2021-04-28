cmake_minimum_required(VERSION 3.0.0)
project(opengl_test VERSION 0.1.0)

add_executable(
    opengl_test

    src/main.cpp

    src/window/window.cpp
    src/window/window.hpp
    src/primitive/primitive.cpp
    src/primitive/primitive.hpp
    src/shader_program/shader_program.cpp
    src/shader_program/shader_program.hpp
)

find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(opengl_test GLEW::GLEW)
target_link_libraries(opengl_test glfw)

# link OPENGL
target_link_libraries(opengl_test GL)

# include_directories(src/window)
