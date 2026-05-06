#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include "../domain/FlyingObject.h"

class ObjectManager {
public:
    ObjectManager();
    void update(double dt);
    std::vector<FlyingObject*> getObjects() const;
    void addObject(std::unique_ptr<FlyingObject> obj);

private:
    mutable std::shared_mutex mutex_;
    std::vector<std::unique_ptr<FlyingObject>> objects_;
};

#endif
