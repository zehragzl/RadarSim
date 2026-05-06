#include "../../include/core/FlyingObjectFactory.h"
#include "../../include/domain/Aircraft.h"
#include "../../include/domain/Helicopter.h"
#include "../../include/domain/UAV.h"

std::unique_ptr<FlyingObject> FlyingObjectFactory::create(
    const std::string& type,
    int id,
    const Vector2D& position,
    const Vector2D& velocity,
    double altitude)
{
    if (type == "Aircraft")
        return std::make_unique<Aircraft>(id, position, velocity, altitude);
    if (type == "Helicopter")
        return std::make_unique<Helicopter>(id, position, velocity, altitude);
    if (type == "UAV")
        return std::make_unique<UAV>(id, position, velocity, altitude);
    return nullptr;
}
