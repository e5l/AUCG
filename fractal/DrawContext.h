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

    void zoomIn(double x, double y);
    void zoomOut(double x, double y);

    void move(double x, double y);

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

    float step = 0.005;
    float ratio = 0.9;

    const uint32_t width = 800;
    const uint32_t height = 600;
};
