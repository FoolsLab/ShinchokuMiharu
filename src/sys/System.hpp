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
    auto getCursorPos() const { return cursorPos; }

  public:
    class Cursor : public ICursor {
        System& sys;

      public:
        Cursor(System& _sys) : sys(_sys) {}
        Cursor(Cursor&) = delete;
        Cursor(Cursor&&) = delete;
        Point getPos() const override { return sys.getCursorPos(); }
    };

  private:
    Cursor cursor;

  public:
    void update() {
        glfwManager.update();
        monitorManager.update();
        mainWindow.update();
        updateCursorPos();
    }
    auto& getCursor() const { return cursor; }
    auto& getWindow() { return mainWindow; }
    auto& getMonitorManager() { return monitorManager; }

    bool shouldExit() const { return mainWindow.CloseRequested(); }

    System() : cursor(*this) {}
    ~System() {}
};
