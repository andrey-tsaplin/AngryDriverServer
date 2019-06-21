//
// Created by andrew on 2/22/17.
//

#pragma once

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <vector>
#include <rapidjson/document.h>

class Model
{
protected:
    std::vector<b2Body *> bodies_;
    std::vector<b2Joint *> joints_;

public:
    Model() {};

    virtual void Spawn(b2World *world, b2Vec2 position) = 0;

    virtual void Destroy(b2World *world) = 0;

    virtual void Step(double deltaTime) {};

    std::vector<b2Body *> GetBodies();

    void ToJson(rapidjson::Document &json) const;
};
