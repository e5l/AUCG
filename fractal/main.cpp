#include "DrawContext.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <cstdio>

DrawContext *context;

struct {
    bool pressed = false;
    double x = 0;
    double y = 0;
} mouse;

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
        default:
            break;
    }
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button != GLFW_MOUSE_BUTTON_LEFT) {
        return;
    }

    if (action == GLFW_PRESS) {
        mouse.pressed = true;
        return;
    }

    mouse.pressed = false;
}

void mouseMoveCallback(GLFWwindow *window, double x, double y) {
    if (mouse.pressed) {
        context->move(x - mouse.x, y - mouse.y);
    }

    mouse.x = x;
    mouse.y = y;
}

void mouseScrollCallback(GLFWwindow* window, double x, double y) {
    if (y > 0) {
        context->zoomIn(mouse.x, mouse.y);
    } else {
        context->zoomOut(mouse.x, mouse.y);
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
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);

    do {
        context->drawFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwWindowShouldClose(window) == 0);

    delete context;
    glfwTerminate();
    return 0;
}