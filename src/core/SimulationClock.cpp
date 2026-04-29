#include "../../include/core/SimulationClock.h"
#include <QDateTime>

SimulationClock::SimulationClock(QObject* parent) : QObject(parent), timer_(new QTimer(this)), lastTime_(0) {
    connect(timer_, &QTimer::timeout, this, &SimulationClock::onTimeout);
}

void SimulationClock::start() {
    if (!timer_->isActive()) {
        lastTime_ = QDateTime::currentDateTime().toMSecsSinceEpoch();
        timer_->start(16); // Approx. 60 FPS
    }
}

void SimulationClock::stop() {
    if (timer_->isActive()) {
        timer_->stop();
    }
}

bool SimulationClock::isRunning() const {
    return timer_->isActive();
}

void SimulationClock::onTimeout() {
    qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    double dt = (currentTime - lastTime_) / 1000.0; // Convert ms to seconds
    lastTime_ = currentTime;
    emit tick(dt);
}