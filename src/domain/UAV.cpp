#include "../../include/domain/UAV.h"

UAV::UAV(int id, const Vector2D& position, const Vector2D& velocity, double altitude,
         double boundaryLimit)
    : FlyingObject(id, position, velocity, altitude), boundaryLimit_(boundaryLimit) {}

void UAV::update(double deltaSeconds) {
    pos_ = pos_ + vel_ * deltaSeconds;

    if (pos_.getX() > boundaryLimit_ || pos_.getX() < -boundaryLimit_)
        vel_.setX(-vel_.getX());
    if (pos_.getY() > boundaryLimit_ || pos_.getY() < -boundaryLimit_)
        vel_.setY(-vel_.getY());
}   

double UAV::radarCrossSection() const {
    return 0.01;
}

std::string UAV::typeName() const {
    return "UAV";
}

