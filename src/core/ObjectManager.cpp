#include "../../include/core/ObjectManager.h"  
#include "../../include/domain/Aircraft.h"
#include "../../include/domain/Helicopter.h"
#include "../../include/domain/UAV.h"

using namespace std;

ObjectManager::ObjectManager() {
    objects_.push_back(make_unique<Aircraft>(1, Vector2D(50, 80), Vector2D(-20, -10), 8000));
    objects_.push_back(make_unique<Aircraft>(2, Vector2D(-100, 30), Vector2D(30, 5), 10000));

    auto heli = make_unique<Helicopter>(3, Vector2D(20, -40), Vector2D(5, 5), 500);
    heli->setWaypoints({Vector2D(20,-40), Vector2D(50,0), Vector2D(20,40)});
    objects_.push_back(std::move(heli));

    objects_.push_back(make_unique<Helicopter>(4, Vector2D(-60, 70), Vector2D(0, 0), 300));
    objects_.push_back(make_unique<UAV>(5, Vector2D(120, -80), Vector2D(-15, 20), 1500));
    objects_.push_back(make_unique<UAV>(6, Vector2D(-30, -120), Vector2D(10, 15), 800));
}

void ObjectManager::addObject(std::unique_ptr<FlyingObject> obj) {
    objects_.push_back(std::move(obj));
}
                                                                                              
std::vector<FlyingObject*> ObjectManager::getObjects() const {
    std::vector<FlyingObject*> result;
    for (const auto& obj : objects_) {
        result.push_back(obj.get());
    }
    return result;
}
void ObjectManager::update(double dt) {
    for (auto& obj : objects_) {
        obj->update(dt);
    }
}

