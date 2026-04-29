#include "../../include/domain/Aircraft.h"

Aircraft::Aircraft(int id, const Vector2D& position, const Vector2D& velocity, double altitude)
    : FlyingObject(id, position, velocity, altitude) {}

void Aircraft::update(double deltaSeconds) {
    pos_ = pos_ + vel_ * deltaSeconds;
}

double Aircraft::radarCrossSection() const {
    return 1.0;
}

std::string Aircraft::typeName() const {
    return "Aircraft";
}
