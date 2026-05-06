#include "../../include/core/ObjectManager.h"

ObjectManager::ObjectManager() {}

void ObjectManager::addObject(std::unique_ptr<FlyingObject> obj) {
    std::unique_lock lock(mutex_);
    objects_.push_back(std::move(obj));
}

void ObjectManager::update(double dt) {
    std::unique_lock lock(mutex_);
    for (auto& obj : objects_)
        obj->update(dt);
}

std::vector<FlyingObject*> ObjectManager::getObjects() const {
    std::shared_lock lock(mutex_);
    std::vector<FlyingObject*> result;
    result.reserve(objects_.size());
    for (const auto& obj : objects_)
        result.push_back(obj.get());
    return result;
}
