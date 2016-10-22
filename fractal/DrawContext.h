#pragma once

#include <GL/glew.h>

#include <functional>

struct DrawContext {

    DrawContext();
    ~DrawContext();

    void drawFrame();

    void updateMaxIterations(std::function<uint32_t(uint32_t)> updater) {
        max_iterations = updater(max_iterations);
    }

    void zoomIn();
    void zoomOut();
    void left();
    void right();
    void up();
    void down();

private:
    const char* VERTEX_SHADER_PATH = "shaders/simple.vertexshader";
    const char* FRAGMENT_SHADER_PATH = "shaders/simple.fragmentshader";

    GLuint program_id;
    GLuint vertex_array_id;
    GLuint vertex_buffer;

    GLint max_iterations_location;
    GLint horizontal_location;
    GLint vertical_location;

    uint32_t max_iterations = 100;

    GLfloat horizontal[2] = {-2.0f, 2.0f};
    GLfloat vertical[2] = {-2.0f, 2.0f};

    float step = 0.5;
    float ratio = 0.9;
};
