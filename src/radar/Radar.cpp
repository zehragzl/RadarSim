#include "../../include/radar/Radar.h"
#include <cmath>

Radar::Radar(double rangeKm, double minRCS)
    : rangeKm_(rangeKm), minRCS_(minRCS) {}

void Radar::scan(const std::vector<FlyingObject*>& objects, const IFFSystem& iff) {
    tracks_.clear();

    for (const auto* obj : objects) {
        double dist = calcDistance(obj->position());

        if (dist > rangeKm_) continue;
        if (obj->radarCrossSection() < minRCS_) continue;

        Track t;
        t.id                = obj->id();
        t.typeName          = obj->typeName();
        t.lastKnownPosition = obj->position();
        t.velocity          = obj->velocity();
        t.altitude          = obj->altitude();
        t.distanceKm        = dist;
        t.iff               = iff.classify(obj->id());

        tracks_.push_back(t);
    }
}

const std::vector<Track>& Radar::getTracks() const {
    return tracks_;
}

double Radar::rangeKm() const {
    return rangeKm_;
}

double Radar::calcDistance(const Vector2D& pos) const {
    return pos.length();
}
