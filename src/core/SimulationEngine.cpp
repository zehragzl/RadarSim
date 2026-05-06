#include "../../include/core/SimulationEngine.h"
#include <chrono>

static constexpr int TICK_MS = 50; // ~20 Hz

SimulationEngine::SimulationEngine(ObjectManager& manager)
    : manager_(manager), running_(false) {}

SimulationEngine::~SimulationEngine() {
    stop();
}

void SimulationEngine::start() {
    if (running_) return;
    running_ = true;
    thread_ = std::thread(&SimulationEngine::run, this);
}

void SimulationEngine::stop() {
    running_ = false;
    if (thread_.joinable())
        thread_.join();
}

void SimulationEngine::setOnSnapshot(std::function<void()> cb) {
    onSnapshot_ = std::move(cb);
}

void SimulationEngine::run() {
    using clock = std::chrono::steady_clock;
    auto prev = clock::now();

    while (running_) {
        auto now = clock::now();
        double dt = std::chrono::duration<double>(now - prev).count();
        prev = now;

        manager_.update(dt);

        if (onSnapshot_)
            onSnapshot_();

        std::this_thread::sleep_for(std::chrono::milliseconds(TICK_MS));
    }
}
