#pragma once

#include "Monitor.hpp"
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <exception>

class GLFWManager {
  public:
    GLFWManager() {
        if (!glfwInit()) {
            throw std::exception("GLFW initialize error");
        }
    }
    ~GLFWManager() { glfwTerminate(); }
    void update() { glfwPollEvents(); }
};

class System {
    GLFWManager glfwManager;
    Window mainWindow;
    Point cursorPos;

    MonitorManager monitorManager;

    void updateCursorPos() {
        cursorPos = mainWindow.getCursorPos() + mainWindow.getWindowPos();
    }

  public:
    void update() {
        glfwManager.update();
        mainWindow.update();
        updateCursorPos();
    }
    auto getCursorPos() const { return cursorPos; }
    auto& getWindow() { return mainWindow; }

    bool shouldExit() const { return mainWindow.CloseRequested(); }

    System() {}
    ~System() {}
};
