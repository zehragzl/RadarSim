#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include "../core/Vector2D.h"
#include <string>

class FlyingObject {
    public:
        virtual ~FlyingObject() = default;
        virtual void update(double deltaSeconds) = 0; 
        virtual double radarCrossSection() const = 0;  
        virtual std::string typeName() const = 0;

        Vector2D position() const;
        Vector2D velocity() const;
        double altitude() const;
        int id() const;
        
    protected:
        FlyingObject(int id, const Vector2D& pos, const Vector2D& vel, double alt)
            : id_(id), pos_(pos), vel_(vel), altitude_(alt) {}   
        Vector2D pos_;
        Vector2D vel_;
        double altitude_;
        int id_;
};

#endif