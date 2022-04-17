#pragma once

#include "../app/Charactor.hpp"
#include "../common/Vec.hpp"
#include <GLFW/glfw3.h>
#include <exception>

class WindowRenderContext : public IRenderContext {
    bool invalid;
    Size viewportSize;
    GLFWwindow *window;

    void procRenderBegin() {
        glfwMakeContextCurrent(window);
    }
    void procRenderEnd() {
        glfwSwapBuffers(window);
    }

  public:
    WindowRenderContext(Size viewportSize, GLFWwindow *window)
        : viewportSize(viewportSize), window(window), invalid(false) {
        procRenderBegin();
    }
    WindowRenderContext(WindowRenderContext&& c)
        : viewportSize(c.viewportSize), window(c.window), invalid(c.invalid) {
        c.invalid = true;
    }
    ~WindowRenderContext() override {
        if (!invalid) {
            procRenderEnd();
            invalid = true;
        }
    }

    void Draw(const Texture& tex, Point dstPos) const override {
        tex.Draw(viewportSize, dstPos);
    }
    void Draw(const Texture& tex, const Point dstPos, const Point srcPos,
              const Size srcRect) const override {
        tex.Draw(viewportSize, dstPos, srcPos, srcRect);
    }
    void Draw(const Texture& tex, const Point dstPos, const Point srcPos,
              const Size srcRect, float scale) const override {
        tex.Draw(viewportSize, dstPos, srcPos, srcRect, scale);
    }
};

class Window : public IWindow {
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
        glfwSwapInterval(1);
        glfwDefaultWindowHints();
        glfwShowWindow(window);
    }

    bool CloseRequested() const override {
        return glfwWindowShouldClose(window) != 0;
    }

    void update() {
        wPos = getWindowPos();
        wSize = getWindowSize();
    }

    auto getCursorPos() const {
        Vec2<double> tmpCPos;
        glfwGetCursorPos(window, &tmpCPos.x, &tmpCPos.y);

        return Point(tmpCPos);
    }

    void setWindowPos(Point newPos) override {
        glfwSetWindowPos(window, newPos.x, newPos.y);
        wPos = newPos;
    }
    Point getWindowPos() const override {
        Vec2<int> tmpWPos;
        glfwGetWindowPos(window, &tmpWPos.x, &tmpWPos.y);
        return Point(tmpWPos);
    }

    void setWindowSize(Size newSize) override {
        glfwSetWindowSize(window, newSize.x, newSize.y);
        wSize = newSize;
    }
    Size getWindowSize() const override {
        Vec2<int> tmpWSize;
        glfwGetWindowSize(window, &tmpWSize.x, &tmpWSize.y);
        return Size(tmpWSize);
    }

    [[nodiscard]] std::unique_ptr<IRenderContext> renderBegin() const override {
        return std::make_unique<WindowRenderContext>(wSize, window);
    }
};
