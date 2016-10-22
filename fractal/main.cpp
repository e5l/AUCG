#include "DrawContext.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <cstdio>

DrawContext *context;

void printGlInfo() {
    using namespace std;
    printf("Renderer: %s\nVersion: %s\n",
           glGetString(GL_RENDER),
           glGetString(GL_VERSION));
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) {
        return;
    }

    switch (key) {
        case GLFW_KEY_Q:
            context->updateMaxIterations([](uint32_t old) { return old + 10; });
            break;
        case GLFW_KEY_A:
            context->updateMaxIterations([](uint32_t old) {
                if (old < 10) return 0;
                return static_cast<int32_t>(old) - 10;
            });
            break;
        case GLFW_KEY_UP:
            context->up();
            break;
        case GLFW_KEY_DOWN:
            context->down();
            break;
        case GLFW_KEY_LEFT:
            context->left();
            break;
        case GLFW_KEY_RIGHT:
            context->right();
            break;
        case GLFW_KEY_Z:
            context->zoomIn();
            break;
        case GLFW_KEY_X:
            context->zoomOut();
        default:
            break;
    }
}

int main() {

    if (!glfwInit()) {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Task 1. Fractal", nullptr, nullptr);
    if (!window) {
        return 1;
    }


    glfwMakeContextCurrent(window);

    glewExperimental = (GLboolean) true;
    glewInit();
    printGlInfo();

    context = new DrawContext();
    glfwSetKeyCallback(window, keyCallback);

    do {
        context->drawFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwWindowShouldClose(window) == 0);

    delete context;
    glfwTerminate();
    return 0;
}