//
// Created by andrew on 3/14/17.
//

// Thanks to Chris Campbell:
// https://www.iforce2d.net/b2dtut/top-down-car

#pragma once


#include "../Model.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <vector>
#include <set>

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

enum {
    TDC_LEFT = 0x1,
    TDC_RIGHT = 0x2,
    TDC_UP = 0x4,
    TDC_DOWN = 0x8
};

class CarTire : public Model
{
    float maxForwardSpeed_;
    float maxBackwardSpeed_;
    float maxDriveForce_;
    float maxLateralImpulse_;
    float currentTraction_;

public:
    b2Body *body_;

    CarTire();

    void Spawn(b2World *world, b2Vec2 position) override;

    void Destroy(b2World *world) override;

    void SetCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse);

    void UpdateTraction();

    b2Vec2 GetLateralVelocity();

    b2Vec2 GetForwardVelocity();

    void UpdateFriction();

    void UpdateDrive(int controlState);

    void UpdateTurn(int controlState);
};


