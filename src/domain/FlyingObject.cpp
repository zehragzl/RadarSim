#include "../../include/domain/FlyingObject.h"

Vector2D FlyingObject::position() const { return pos_; }
Vector2D FlyingObject::velocity() const { return vel_; }
double FlyingObject::altitude() const { return altitude_; }
int FlyingObject::id() const { return id_; }
