//
// Created by andrew on 3/14/17.
//

#include "CarBody.h"

void CarBody::Spawn(b2World *world, b2Vec2 position)
{
    //create car body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.x = position.x;
    bodyDef.position.y = position.y;
    body_ = world->CreateBody(&bodyDef);
    body_->SetAngularDamping(3);

    b2Vec2 vertices[8];
    vertices[0].Set(1.5, 0);
    vertices[1].Set(3, 2.5);
    vertices[2].Set(2.8, 5.5);
    vertices[3].Set(1, 10);
    vertices[4].Set(-1, 10);
    vertices[5].Set(-2.8, 5.5);
    vertices[6].Set(-3, 2.5);
    vertices[7].Set(-1.5, 0);
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 8);
    b2Fixture *fixture = body_->CreateFixture(&polygonShape, 0.1f);
    bodies_.push_back(body_);

    //prepare common joint parameters
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body_;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;
    jointDef.upperAngle = 0;
    jointDef.localAnchorB.SetZero();

    float maxForwardSpeed = 350;
    float maxBackwardSpeed = -80;
    float backTireMaxDriveForce = 300;
    float frontTireMaxDriveForce = 500;
    float backTireMaxLateralImpulse = 9.5;
    float frontTireMaxLateralImpulse = 8.5;

    //back left tire
    auto *tire = new CarTire();
    tire->Spawn(world, position);
    tire->SetCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointDef.bodyB = tire->body_;
    jointDef.localAnchorA.Set(-3, 0.75f);
    world->CreateJoint(&jointDef);
    tires_.push_back(tire);
    bodies_.push_back(tire->body_);

    //back right tire
    tire = new CarTire();
    tire->Spawn(world, position);
    tire->SetCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointDef.bodyB = tire->body_;
    jointDef.localAnchorA.Set(3, 0.75f);
    world->CreateJoint(&jointDef);
    tires_.push_back(tire);
    bodies_.push_back(tire->body_);

    //front left tire
    tire = new CarTire();
    tire->Spawn(world, position);
    tire->SetCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointDef.bodyB = tire->body_;
    jointDef.localAnchorA.Set(-3, 8.5f);
    flJoint_ = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
    tires_.push_back(tire);
    bodies_.push_back(tire->body_);

    //front right tire
    tire = new CarTire();
    tire->Spawn(world, position);
    tire->SetCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointDef.bodyB = tire->body_;
    jointDef.localAnchorA.Set(3, 8.5f);
    frJoint_ = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
    tires_.push_back(tire);
    bodies_.push_back(tire->body_);
}

void CarBody::Destroy()
{
    for (auto tire : tires_)
    {
        delete tire;
    }

    body_->GetWorld()->DestroyBody(body_);
}

void CarBody::SetControlState(int controlState)
{
    controlState_ = controlState;
}

void CarBody::Step(double deltaTime)
{
    for (auto tire : tires_)
    {
        tire->UpdateFriction();
    }

    for (auto tire : tires_)
    {
        tire->UpdateDrive(controlState_);
    }

    //control steering
    float lockAngle = 45 * DEGTORAD;
    float turnSpeedPerSec = 160 * DEGTORAD;
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = 0;
    switch (controlState_ & (TDC_LEFT | TDC_RIGHT))
    {
        case TDC_LEFT:
            desiredAngle = -lockAngle;
            break;
        case TDC_RIGHT:
            desiredAngle = lockAngle;
            break;
        default:;//nothing
    }

    float angleNow = flJoint_->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;
    flJoint_->SetLimits(newAngle, newAngle);
    frJoint_->SetLimits(newAngle, newAngle);
}

CarBody::~CarBody()
{
    Destroy();
}

