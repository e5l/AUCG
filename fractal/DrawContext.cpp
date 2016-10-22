
#include "DrawContext.h"
#include "utils.h"

DrawContext::DrawContext()
        : program_id(loadShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH)) {

    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    static const GLfloat vertex_buffer_data[] = {
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    max_iterations_location = glGetUniformLocation(program_id, "max_iterations");
    horizontal_location = glGetUniformLocation(program_id, "horizontal");
    vertical_location = glGetUniformLocation(program_id, "vertical");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

DrawContext::~DrawContext() {
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array_id);
    glDeleteProgram(program_id);
}

void DrawContext::drawFrame() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUniform1i(max_iterations_location, max_iterations);
    glUniform2f(horizontal_location, horizontal[0], horizontal[1]);
    glUniform2f(vertical_location, vertical[0], vertical[1]);

    glUseProgram(program_id);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(0);
}

void DrawContext::zoomIn() {
    float hsize = (horizontal[1] - horizontal[0]) / 2;
    float vsize = (vertical[1] - vertical[0]) / 2;

    float hc = (horizontal[1] + horizontal[0]) / 2;
    float vc = (vertical[1] + vertical[0]) / 2;

    horizontal[0] = (hc - hsize * ratio);
    horizontal[1] = (hc + hsize * ratio);

    vertical[0] = (vc - vsize * ratio);
    vertical[1] = (vc + vsize * ratio);

    step *= ratio;
}

void DrawContext::zoomOut() {
    float hsize = (horizontal[1] - horizontal[0]) / 2;
    float vsize = (vertical[1] - vertical[0]) / 2;

    float hc = (horizontal[1] + horizontal[0]) / 2;
    float vc = (vertical[1] + vertical[0]) / 2;

    float invratio = 2.0f - ratio;
    horizontal[0] = (hc - hsize * invratio);
    horizontal[1] = (hc + hsize * invratio);

    vertical[0] = (vc - vsize * invratio);
    vertical[1] = (vc + vsize * invratio);

    step *= invratio;
}

void DrawContext::left() {
    horizontal[0] -= step;
    horizontal[1] -= step;
}

void DrawContext::right() {
    horizontal[0] += step;
    horizontal[1] += step;
}

void DrawContext::up() {
    vertical[0] += step;
    vertical[1] += step;
}

void DrawContext::down() {
    vertical[0] -= step;
    vertical[1] -= step;
}
