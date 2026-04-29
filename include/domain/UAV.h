#ifndef UAV_H
#define UAV_H

#include "FlyingObject.h"
#include "../core/Vector2D.h"
#include <vector>
#include <string>


class UAV : public FlyingObject {
    public:
        UAV(int id, const Vector2D& position, const Vector2D& velocity, double altitude,
            double boundaryLimit = 250.0);
        void update(double deltaSeconds) override;
        double radarCrossSection() const override;
        std::string typeName() const override;

    private:
        double boundaryLimit_;
};

#endif