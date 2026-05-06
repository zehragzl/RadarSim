#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <thread>
#include <atomic>
#include <functional>
#include "ObjectManager.h"

class SimulationEngine {
public:
    explicit SimulationEngine(ObjectManager& manager);
    ~SimulationEngine();

    void start();
    void stop();

    void setOnSnapshot(std::function<void()> cb);

private:
    ObjectManager& manager_;
    std::thread thread_;
    std::atomic<bool> running_;
    std::function<void()> onSnapshot_;

    void run();
};

#endif
