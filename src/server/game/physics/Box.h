//
// Created by andrew on 3/2/17.
//

#pragma once

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "Box2D/Dynamics/b2Body.h"
#include "Model.h"

static const int DEFAULT_DENSITY = 1;
static const int DEFAULT_RESTITUTION = 0.2;
static const int DEFAULT_FRICTION = 0.3;

class Box : public Model
{
protected:
    float height_;
    float width_;
    bool dynamic_;

public:
    Box(float width, float height, bool dynamic);

    void Spawn(b2World *world, b2Vec2 position) override;

    void Destroy(b2World *world) override;
};
