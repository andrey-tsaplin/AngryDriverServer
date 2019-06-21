//
// Created by andrew on 2/22/17.
//

#pragma once

#include "rapidjson/document.h"

/* OBJECT TYPES */
static const int GAME_OBJECT_UNKNOWN = 0;
static const int GAME_OBJECT_PLAYER = 2;
static const int GAME_OBJECT_PHYSICS = 3;

class Engine;
class Level;

/* Object on level */
class Object
{
protected:
    int type_;
    Engine *engine_;
    Level *level_;

public:
    Object(int type, Engine *engine, Level *level);

    int GetType();

    bool Is(int type);

    virtual void Spawn();

    virtual void Step(double deltaTime) = 0;

    virtual void ToJson(rapidjson::Document &json) const;

    virtual ~Object();
};
