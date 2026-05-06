#ifndef RADAR_H
#define RADAR_H

#include <vector>
#include "../domain/FlyingObject.h"
#include "IFFSystem.h"
#include "Track.h"

class Radar {
public:
    explicit Radar(double rangeKm = 250.0, double minRCS = 0.005);

    void scan(const std::vector<FlyingObject*>& objects, const IFFSystem& iff);

    const std::vector<Track>& getTracks() const;
    double rangeKm() const;

private:
    double rangeKm_;
    double minRCS_;
    std::vector<Track> tracks_;

    double calcDistance(const Vector2D& pos) const;
};

#endif
