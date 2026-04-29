#include "../../include/core/Vector2D.h"

Vector2D Vector2D::operator+(const Vector2D &other) const {
  return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D &other) const {
  return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(double scalar) const {
  return Vector2D(x * scalar, y * scalar);
}

double Vector2D::length() const { return std::sqrt(x * x + y * y); }

double Vector2D::distanceOf(const Vector2D &other) const {
  return (*this - other).length();
}

Vector2D Vector2D::normalize() const {
  double mag = length();
  if (mag == 0.0)
    return Vector2D(0, 0);
  return Vector2D(x / mag, y / mag);
}

double Vector2D::dot(const Vector2D &other) const {
  return x * other.x + y * other.y;
}
