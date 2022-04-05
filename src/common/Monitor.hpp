#pragma once

#include "utils/utils.hpp"
#include <GLFW/glfw3.h>
#include <exception>
#include <vector>

struct Monitor {
    Point origin;
    Size size;
    Scale scale;
    bool isCoordInMonitor(const Point pos) const {
        return origin.x <= pos.x && pos.x < origin.x + size.x &&
               origin.y <= pos.y && pos.y < origin.y + size.y;
    }

    Monitor() {}
    Monitor(GLFWmonitor *glfwMonitor) {
        const GLFWvidmode *videoMode = glfwGetVideoMode(glfwMonitor);
        size.x = videoMode->width;
        size.y = videoMode->height;

        Vec2<int> tmpPos;
        glfwGetMonitorPos(glfwMonitor, &tmpPos.x, &tmpPos.y);
        origin = tmpPos;

        Vec2<float> tmpScale;
        glfwGetMonitorContentScale(glfwMonitor, &tmpScale.x, &tmpScale.y);
        scale = tmpScale;
    }
};

class MonitorManager {
    std::vector<Monitor> monitors;

  public:
    void update() {
        int count;
        auto pMonitors = glfwGetMonitors(&count);
        monitors.resize(count);
        for (size_t i = 0; i < count; i++) {
            monitors[i] = Monitor(pMonitors[i]);
        }
    }

    int getMonitorIndexFromCoord(const Point pos) const {
        for (int i = 0; const auto &monitor : monitors) {
            if (monitor.isCoordInMonitor(pos)) {
                return i;
            }
            i++;
        }
        return -1;
    }
    auto getMonitorFromCoord(const Point pos) const {
        int index = getMonitorIndexFromCoord(pos);
        if (index == -1) {
            throw std::exception("monitor get error");
        }
        return monitors[index];
    }
    auto getMonitor(const size_t index) const { return monitors[index]; }
};
