#pragma once

#include "utils/utils.hpp"
#include <GLFW/glfw3.h>
#include <exception>

class Window {
    GLFWwindow *window;

    Point wPos;

  public:
    Window() {
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window) {
            throw std::exception("Window creation error");
        }

        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
        glfwMakeContextCurrent(window);
        glfwDefaultWindowHints();
        glfwShowWindow(window);
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
