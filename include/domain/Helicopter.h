#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "FlyingObject.h"
#include "../core/Vector2D.h"
#include <vector>
#include <string>

class Helicopter : public FlyingObject {
    public:
        Helicopter(int id, const Vector2D& position, const Vector2D& velocity, double altitude);
        void update(double deltaSeconds) override;
        double radarCrossSection() const override;
        std::string typeName() const override;
        void setWaypoints(std::vector<Vector2D> waypoints);

    private:
        std::vector<Vector2D> waypoints_;
        size_t currentWaypointIndex_;
       
};
#endif