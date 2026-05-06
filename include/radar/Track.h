#ifndef TRACK_H
#define TRACK_H

#include <string>
#include "../core/Vector2D.h"
#include "IFFSystem.h"

struct Track {
    int id;
    std::string typeName;
    Vector2D lastKnownPosition;
    Vector2D velocity;
    double altitude;
    double distanceKm;
    IFFStatus iff;
};

#endif
