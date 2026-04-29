#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>

class Vector2D {
private:
  double x;
  double y;

public:
  Vector2D(){};
  Vector2D(double x, double y) : x(x), y(y) {}

  Vector2D operator+(const Vector2D &other) const;
  Vector2D operator-(const Vector2D &other) const;
  Vector2D operator*(double scalar) const;

  double length() const;
  double distanceOf(const Vector2D &other) const;
  Vector2D normalize() const;
  double dot(const Vector2D &other) const;

  // getter methods
  double getX() const { return x; }
  double getY() const { return y; }

  // setters method
  void setX(double x) { this->x = x; }
  void setY(double y) { this->y = y; }
};

#endif