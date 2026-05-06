#ifndef FLYINGOBJECTFACTORY_H
#define FLYINGOBJECTFACTORY_H

#include <memory>
#include <string>
#include "../domain/FlyingObject.h"
#include "../core/Vector2D.h"

class FlyingObjectFactory {
public:
    static std::unique_ptr<FlyingObject> create(
        const std::string& type,
        int id,
        const Vector2D& position,
        const Vector2D& velocity,
        double altitude);
};

#endif
