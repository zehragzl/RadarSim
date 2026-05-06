#include "../../include/core/ObjectManager.h"
#include "../../include/domain/Aircraft.h"
#include "../../include/domain/Helicopter.h"
#include "../../include/domain/UAV.h"

using namespace std;

ObjectManager::ObjectManager() {
    // Aircraft'lar
    objects_.push_back(make_unique<Aircraft>(1,  Vector2D(50, 80),    Vector2D(-20, -10), 8000));
    objects_.push_back(make_unique<Aircraft>(2,  Vector2D(-100, 30),  Vector2D(30, 5),    10000));
    objects_.push_back(make_unique<Aircraft>(3,  Vector2D(80, -60),   Vector2D(-10, 25),  9000));
    objects_.push_back(make_unique<Aircraft>(4,  Vector2D(-40, -90),  Vector2D(20, 10),   7500));
    objects_.push_back(make_unique<Aircraft>(5,  Vector2D(110, 40),   Vector2D(-25, -5),  11000));
    objects_.push_back(make_unique<Aircraft>(6,  Vector2D(-70, 110),  Vector2D(15, -20),  8500));
    objects_.push_back(make_unique<Aircraft>(7,  Vector2D(30, -130),  Vector2D(-5, 30),   9500));
    objects_.push_back(make_unique<Aircraft>(8,  Vector2D(-120, -50), Vector2D(35, 10),   10500));
    objects_.push_back(make_unique<Aircraft>(9,  Vector2D(60, 100),   Vector2D(-15, -25), 7000));
    objects_.push_back(make_unique<Aircraft>(10, Vector2D(-90, -30),  Vector2D(20, -15),  8000));
    objects_.push_back(make_unique<Aircraft>(11, Vector2D(140, -70),  Vector2D(-30, 10),  9000));
    objects_.push_back(make_unique<Aircraft>(12, Vector2D(-150, 60),  Vector2D(25, -5),   10000));

    // Helicopter'lar
    auto h1 = make_unique<Helicopter>(13, Vector2D(20, -40), Vector2D(5, 5), 500);
    h1->setWaypoints({Vector2D(20,-40), Vector2D(50,0), Vector2D(20,40)});
    objects_.push_back(std::move(h1));

    objects_.push_back(make_unique<Helicopter>(14, Vector2D(-60, 70),  Vector2D(0, 0),   300));
    objects_.push_back(make_unique<Helicopter>(15, Vector2D(90, 20),   Vector2D(-8, 8),  400));
    objects_.push_back(make_unique<Helicopter>(16, Vector2D(-30, -80), Vector2D(6, -6),  350));
    objects_.push_back(make_unique<Helicopter>(17, Vector2D(10, 110),  Vector2D(-5, -5), 450));
    objects_.push_back(make_unique<Helicopter>(18, Vector2D(-100, 0),  Vector2D(7, 3),   500));
    objects_.push_back(make_unique<Helicopter>(19, Vector2D(70, -90),  Vector2D(-6, 9),  300));
    objects_.push_back(make_unique<Helicopter>(20, Vector2D(-50, 50),  Vector2D(4, -7),  400));
    objects_.push_back(make_unique<Helicopter>(21, Vector2D(40, 60),   Vector2D(-9, 4),  350));
    objects_.push_back(make_unique<Helicopter>(22, Vector2D(-80, -60), Vector2D(5, 8),   450));

    // UAV'lar
    objects_.push_back(make_unique<UAV>(23, Vector2D(120, -80),  Vector2D(-15, 20),  1500));
    objects_.push_back(make_unique<UAV>(24, Vector2D(-30, -120), Vector2D(10, 15),   800));
    objects_.push_back(make_unique<UAV>(25, Vector2D(100, 50),   Vector2D(-20, -10), 1200));
    objects_.push_back(make_unique<UAV>(26, Vector2D(-110, 80),  Vector2D(18, -12),  1000));
    objects_.push_back(make_unique<UAV>(27, Vector2D(55, -110),  Vector2D(-12, 22),  1300));
    objects_.push_back(make_unique<UAV>(28, Vector2D(-75, -90),  Vector2D(22, 8),    900));
    objects_.push_back(make_unique<UAV>(29, Vector2D(130, 10),   Vector2D(-18, 15),  1100));
    objects_.push_back(make_unique<UAV>(30, Vector2D(-20, 130),  Vector2D(14, -18),  1400));
    objects_.push_back(make_unique<UAV>(31, Vector2D(85, 75),    Vector2D(-10, -20), 700));
    objects_.push_back(make_unique<UAV>(32, Vector2D(-95, -10),  Vector2D(16, 12),   1600));
    objects_.push_back(make_unique<UAV>(33, Vector2D(25, -100),  Vector2D(-8, 25),   800));
    objects_.push_back(make_unique<UAV>(34, Vector2D(-130, 40),  Vector2D(20, -8),   1200));
    objects_.push_back(make_unique<UAV>(35, Vector2D(75, -40),   Vector2D(-22, 18),  1000));
    objects_.push_back(make_unique<UAV>(36, Vector2D(-55, 95),   Vector2D(12, -22),  900));
    objects_.push_back(make_unique<UAV>(37, Vector2D(115, -100), Vector2D(-16, 14),  1300));
    objects_.push_back(make_unique<UAV>(38, Vector2D(-85, -110), Vector2D(24, 6),    1100));
    objects_.push_back(make_unique<UAV>(39, Vector2D(45, 120),   Vector2D(-14, -16), 700));
    objects_.push_back(make_unique<UAV>(40, Vector2D(-140, 20),  Vector2D(19, -10),  1500));
    objects_.push_back(make_unique<UAV>(41, Vector2D(95, -20),   Vector2D(-21, 17),  800));
    objects_.push_back(make_unique<UAV>(42, Vector2D(-65, -140), Vector2D(11, 21),   1200));
    objects_.push_back(make_unique<UAV>(43, Vector2D(65, 90),    Vector2D(-17, -13), 900));
    objects_.push_back(make_unique<UAV>(44, Vector2D(-105, 55),  Vector2D(23, -9),   1000));
    objects_.push_back(make_unique<UAV>(45, Vector2D(35, -75),   Vector2D(-9, 23),   1400));
    objects_.push_back(make_unique<UAV>(46, Vector2D(-45, 75),   Vector2D(13, -19),  600));
    objects_.push_back(make_unique<UAV>(47, Vector2D(105, 30),   Vector2D(-19, 11),  1100));
    objects_.push_back(make_unique<UAV>(48, Vector2D(-115, -80), Vector2D(26, 7),    700));
    objects_.push_back(make_unique<UAV>(49, Vector2D(15, 145),   Vector2D(-13, -21), 1300));
    objects_.push_back(make_unique<UAV>(50, Vector2D(-160, -30), Vector2D(17, -14),  1600));
}

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
