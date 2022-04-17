#pragma once

#include "../common/Vec.hpp"
#include "../app/Charactor.hpp"
#include <GLFW/glfw3.h>
#include <exception>
#include <mutex>
#include <vector>
#include <unordered_set>

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
    bool invalid;
    static std::vector<Monitor> latestMonitorsInfo;
    static std::unordered_set<MonitorManager*> objList;

    static std::mutex mtx;

    static void updateMonitorInfoGlobal(){
        std::lock_guard<std::mutex> lock(mtx);

        int count;
        auto pMonitors = glfwGetMonitors(&count);

        latestMonitorsInfo.clear();
        for (size_t i = 0; i < count; i++) {
            latestMonitorsInfo.emplace_back(pMonitors[i]);
        }
        for(auto& obj : objList){
            obj->invalid = true;
        }
    }
    static void monitorCallback(GLFWmonitor* monitor, int event){
        updateMonitorInfoGlobal();
    }
  public:
    MonitorManager(){
        bool needGlobalUpdate = false;
        {
            std::lock_guard<std::mutex> lock(mtx);
            if(objList.empty()){
                glfwSetMonitorCallback(monitorCallback);
                objList.insert(this);
                needGlobalUpdate = true;
            }else{
                objList.insert(this);
            }
        }
        if(needGlobalUpdate){
            updateMonitorInfoGlobal();
        }
        update();
    }
    ~MonitorManager(){
        std::lock_guard<std::mutex> lock(mtx);
        objList.erase(this);
        if(objList.empty()){
            glfwSetMonitorCallback(NULL);
        }
    }

    void update() {
        if(this->invalid){
            std::lock_guard<std::mutex> lock(mtx);
            monitors = latestMonitorsInfo;
            this->invalid = false;
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
