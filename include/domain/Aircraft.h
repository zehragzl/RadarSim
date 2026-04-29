#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "FlyingObject.h"
#include "../core/Vector2D.h"
#include <vector>
#include <string>


class Aircraft : public FlyingObject {
    public:
        Aircraft(int id, const Vector2D& position, const Vector2D& velocity, double altitude);
        void update(double deltaSeconds) override;
        double radarCrossSection() const override;
        std::string typeName() const override;
};

#endif