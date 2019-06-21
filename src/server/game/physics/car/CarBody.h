//
// Created by andrew on 3/14/17.
//

#pragma once

#include "CarTire.h"
#include <Box2D/Dynamics/Joints/b2RevoluteJoint.h>

class CarBody : public Model
{
    b2Body *body_ = nullptr;
    std::vector<CarTire *> tires_;
    b2RevoluteJoint *flJoint_, *frJoint_;
    int controlState_;

public:
    CarBody() : Model(){}

    void Spawn(b2World *world, b2Vec2 position) override;

    void Destroy() override;

    void Step(double deltaTime) override;

    void SetControlState(int controlState);

    ~CarBody();
};


