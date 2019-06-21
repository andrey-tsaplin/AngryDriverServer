//
// Created by andrew on 3/14/17.
//

#include "CarTire.h"

CarTire::CarTire() : Model()
{
    currentTraction_ = 1;
}

void CarTire::Spawn(b2World *world, b2Vec2 position)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.x = position.x;
    bodyDef.position.y = position.y;
    body_ = world->CreateBody(&bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(0.5f, 1.25f);
    b2Fixture *fixture = body_->CreateFixture(&polygonShape, 1);//shape, density

    body_->SetUserData(this);
}

void CarTire::Destroy(b2World *world)
{
    body_->GetWorld()->DestroyBody(body_);
}

void
CarTire::SetCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse)
{
    maxForwardSpeed_ = maxForwardSpeed;
    maxBackwardSpeed_ = maxBackwardSpeed;
    maxDriveForce_ = maxDriveForce;
    maxLateralImpulse_ = maxLateralImpulse;
}

void CarTire::UpdateTraction()
{
    currentTraction_ = 1;
}

b2Vec2 CarTire::GetLateralVelocity()
{
    b2Vec2 currentRightNormal = body_->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, body_->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 CarTire::GetForwardVelocity()
{
    b2Vec2 currentForwardNormal = body_->GetWorldVector(b2Vec2(0, 1));
    return b2Dot(currentForwardNormal, body_->GetLinearVelocity()) * currentForwardNormal;
}

void CarTire::UpdateFriction()
{
    //lateral linear velocity
    b2Vec2 impulse = body_->GetMass() * - GetLateralVelocity();
    if (impulse.Length() > maxLateralImpulse_)
        impulse *= maxLateralImpulse_ / impulse.Length();
    body_->ApplyLinearImpulse(currentTraction_ * impulse, body_->GetWorldCenter(), true);

    //angular velocity
    body_->ApplyAngularImpulse(currentTraction_ * 0.1f * body_->GetInertia() * -body_->GetAngularVelocity(),
                               true);

    //forward linear velocity
    b2Vec2 currentForwardNormal = GetForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    body_->ApplyForce(currentTraction_ * dragForceMagnitude * currentForwardNormal, body_->GetWorldCenter(),
                      true);
}

void CarTire::UpdateDrive(int controlState)
{
    float desiredSpeed = 0;
    switch (controlState & (TDC_UP | TDC_DOWN))
    {
        case TDC_UP:
            desiredSpeed = maxForwardSpeed_;
            break;
        case TDC_DOWN:
            desiredSpeed = maxBackwardSpeed_;
            break;
        default:
            //do nothing
            return;
    }

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = body_->GetWorldVector(b2Vec2(0, 1));
    float currentSpeed = b2Dot(GetForwardVelocity(), currentForwardNormal);

    //apply necessary force
    float force = 0;
    if (desiredSpeed > currentSpeed)
        force = maxDriveForce_;
    else if (desiredSpeed < currentSpeed)
        force = -maxDriveForce_;
    else
        return;
    body_->ApplyForce(currentTraction_ * force * currentForwardNormal, body_->GetWorldCenter(), true);
}

void CarTire::UpdateTurn(int controlState)
{
    float desiredTorque = 0;
    switch (controlState & (TDC_LEFT | TDC_RIGHT))
    {
        case TDC_LEFT:
            desiredTorque = -15;
            break;
        case TDC_RIGHT:
            desiredTorque = 15;
            break;
        default:;//nothing
    }
    body_->ApplyTorque(desiredTorque, true);
}