#include "Monitor.hpp"

std::vector<Monitor> MonitorManager::latestMonitorsInfo;
std::unordered_set<MonitorManager*> MonitorManager::objList;

std::mutex MonitorManager::mtx;
