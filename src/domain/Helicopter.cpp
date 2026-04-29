#include "../../include/domain/Helicopter.h"

Helicopter::Helicopter(int id, const Vector2D& position, const Vector2D& velocity, double altitude)
    : FlyingObject(id, position, velocity, altitude), currentWaypointIndex_(0) {}

void Helicopter::update(double deltaSeconds) {
    if (waypoints_.empty()) {
        pos_ = pos_ + vel_ * deltaSeconds;
        return;
    }

    const Vector2D& target = waypoints_[currentWaypointIndex_];
    double dist = pos_.distanceOf(target);

    if (dist < 0.5) {
        vel_ = Vector2D(0, 0);
        currentWaypointIndex_++;
        if (currentWaypointIndex_ >= waypoints_.size())
            currentWaypointIndex_ = 0;
    } else {
        vel_ = (target - pos_).normalize() * 50.0;
        pos_ = pos_ + vel_ * deltaSeconds;
    }
}

void Helicopter::setWaypoints(std::vector<Vector2D> waypoints) {
    waypoints_ = waypoints;
    currentWaypointIndex_ = 0;
}

double Helicopter::radarCrossSection() const {
    return 0.5;
}

std::string Helicopter::typeName() const {
    return "Helicopter";
}
