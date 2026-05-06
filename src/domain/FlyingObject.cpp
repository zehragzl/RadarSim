#include "../../include/domain/FlyingObject.h"

Vector2D FlyingObject::position() const { return pos_; }
Vector2D FlyingObject::velocity() const { return vel_; }
double FlyingObject::altitude() const { return altitude_; }
int FlyingObject::id() const { return id_; }

void FlyingObject::reflectAtBoundary(double boundaryKm) {
    if (pos_.length() > boundaryKm) {
        Vector2D n = pos_.normalize();
        vel_ = vel_ - n * (2.0 * vel_.dot(n));
        pos_ = n * boundaryKm;
    }
}
