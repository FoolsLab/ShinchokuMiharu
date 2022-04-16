#pragma once

#include "../common/Vec.hpp"
#include <GLFW/glfw3.h>
#include <exception>
#include <vector>

struct Monitor : public IMonitor {
    Point origin;
    Size size;
    Scale scale;
    bool isCoordInMonitor(const Point pos) const override {
        return origin.x <= pos.x && pos.x < origin.x + size.x &&
               origin.y <= pos.y && pos.y < origin.y + size.y;
    }

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

class MonitorManager : public IMonitorManager {
    std::vector<Monitor> monitors;

  public:
    void update() {
        int count;
        auto pMonitors = glfwGetMonitors(&count);
        for (size_t i = 0; i < count; i++) {
            monitors.emplace_back(pMonitors[i]);
        }
    }

    int getMonitorIndexFromCoord(const Point pos) const override {
        for (int i = 0; const auto &monitor : monitors) {
            if (monitor.isCoordInMonitor(pos)) {
                return i;
            }
            i++;
        }
        return -1;
    }
    const IMonitor& getMonitorFromCoord(const Point pos) const override {
        int index = getMonitorIndexFromCoord(pos);
        if (index == -1) {
            throw std::exception("monitor get error");
        }
        return monitors[index];
    }
    size_t getMonitorNum() const override { return monitors.size(); }
    const IMonitor& getMonitor(const size_t index) const override { return monitors[index]; }
};
