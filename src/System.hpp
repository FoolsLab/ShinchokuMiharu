#pragma once

#include "Charactor.hpp"
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

    Charactor charactor;

    void updateCursourPos() {
        cursorPos = mainWindow.getCursorPos() + mainWindow.getWindowPos();
    }

  public:
    void update() {
        glfwManager.update();
        mainWindow.update();
        updateCursourPos();

        charactor.update();

        // start render
        mainWindow.renderBegin();

        charactor.draw();

        mainWindow.renderEnd();
        // end render
    }
    auto getCursorPos() const { return cursorPos; }

    bool shouldExit() { return mainWindow.CloseRequested(); }

    System() {}
    ~System() {}
};
