#pragma once

#include "Vec.hpp"
#include <GLFW/glfw3.h>
#include <exception>

class Window {
    GLFWwindow *window;

    Point wPos;
    Size wSize;

  public:
    Window(Size _wSize = {640, 480}) : wSize(_wSize) {
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        window = glfwCreateWindow(wSize.x, wSize.y, "Hello World", NULL, NULL);
        if (!window) {
            throw std::exception("Window creation error");
        }

        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
        glfwMakeContextCurrent(window);
        glfwDefaultWindowHints();
        glfwShowWindow(window);
    }

    bool CloseRequested() const { return glfwWindowShouldClose(window) != 0; }

    void update() {
        Vec2<int> tmpWPos;
        glfwGetWindowPos(window, &tmpWPos.x, &tmpWPos.y);
        wPos = tmpWPos;
        
        Vec2<int> tmpWSize;
        glfwGetWindowSize(window, &tmpWSize.x, &tmpWSize.y);
        wSize = tmpWSize;
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
    
    void setWindowSize(Size newSize) {
        glfwSetWindowSize(window, newSize.x, newSize.y);
        wSize = newSize;
    }
    auto getWindowSize() const { return wSize; }

    void renderBegin() const {
        glfwMakeContextCurrent(window);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void renderEnd() const { glfwSwapBuffers(window); }
};
