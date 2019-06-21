//
// Created by andrew on 3/14/17.
//

#pragma once

#include <Box2D/Dynamics/Joints/b2RevoluteJoint.h>
#include "CarTire.h"

class CarBody : public Model
{
    b2Body *body_;
    std::vector<CarTire *> tires_;
    b2RevoluteJoint *flJoint_, *frJoint_;
    int controlState_;

public:
    CarBody() : Model(){}

    void Spawn(b2World *world, b2Vec2 position);

    void Destroy(b2World *world);

    void SetControlState(int controlState);

    void Step(double deltaTime);
};


