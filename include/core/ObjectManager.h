#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <memory>
#include "../domain/FlyingObject.h"

class ObjectManager {
    private:
        std::vector<std::unique_ptr<FlyingObject>> objects_;

    public:
        ObjectManager();
        void update(double dt);
        std::vector<FlyingObject*> getObjects() const;
        void addObject(std::unique_ptr<FlyingObject> obj);

};

#endif