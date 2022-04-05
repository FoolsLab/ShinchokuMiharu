#pragma once

#include <exception>
#include <GLFW/glfw3.h>
#include "Monitor.hpp"
#include "Window.hpp"

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

    void updateCursourPos() {
        cursorPos = mainWindow.getCursorPos() + mainWindow.getWindowPos();
    }

  public:
    void update() {
        glfwManager.update();
        mainWindow.update();
        updateCursourPos();

        mainWindow.renderBegin();
        mainWindow.renderEnd();
    }
    auto getCursorPos() const { return cursorPos; }

    bool shouldExit() { return mainWindow.CloseRequested(); }

    System() {}
    ~System() {}
};
