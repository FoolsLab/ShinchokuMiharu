#pragma once

#include <exception>
#include <GLFW/glfw3.h>
#include "utils/utils.hpp"

class Window {
    GLFWwindow *window;

    Point wPos;

  public:
    Window() {
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window) {
            throw std::exception("Window creation error");
        }
    }

    bool CloseRequested() { return glfwWindowShouldClose(window) != 0; }

    void update() {
        Vec2<int> tmpWPos;
        glfwGetWindowPos(window, &tmpWPos.x, &tmpWPos.y);
        wPos = tmpWPos;
    }

    auto getCursorPos() const {
        Vec2<double> tmpCPos;
        glfwGetCursorPos(window, &tmpCPos.x, &tmpCPos.y);

        return Point(tmpCPos);
    }

    void setWindowPos(Point newPos) {
        glfwSetWindowPos(window, newPos.x, newPos.y);
        wPos = newPos;
    }
    auto getWindowPos() const { return wPos; }

    void renderBegin() {
        glfwMakeContextCurrent(window);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void renderEnd() { glfwSwapBuffers(window); }
};
