//
// Created by andrew on 2/22/17.
//

#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(Model *model, Engine *engine, Level *level, int type) : Object(type, engine, level)
{
    model_ = model;
}

void PhysicsObject::Step(double deltaTime)
{
    model_->Step(deltaTime);
}

void PhysicsObject::Spawn(b2World *world, b2Vec2 position)
{
    Object::Spawn();
    model_->Spawn(world, position);
}

void PhysicsObject::Destroy()
{
    model_->Destroy();
}

void PhysicsObject::ToJson(rapidjson::Document &json) const
{
    using namespace rapidjson;
    Object::ToJson(json);

    Document modelJson(kObjectType, &json.GetAllocator());
    model_->ToJson(modelJson);

    /*JSON API: m stands for Model data*/
    json.AddMember("m", modelJson, json.GetAllocator());
}

Model *PhysicsObject::GetModel()
{
    return model_;
}

PhysicsObject::~PhysicsObject()
{
    Destroy();
}
