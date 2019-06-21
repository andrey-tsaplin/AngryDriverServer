//
// Created by andrew on 3/3/17.
//

#include "Object.h"
#include "Level.h"

Object::Object(int type, Engine *engine, Level *level)
{
    type_ = type;
    engine_ = engine;
    level_ = level;
};

int Object::GetType()
{
    return type_;
}

bool Object::Is(int type)
{
    return type == type_;
}

void Object::Spawn()
{
    level_->AddObject(this);
}

void Object::ToJson(rapidjson::Document &json) const
{
    using namespace rapidjson;

    /*JSON API: t stands for object's type*/
    json.AddMember("t", Value().SetInt(type_), json.GetAllocator());
}

Object::~Object()
{ }
