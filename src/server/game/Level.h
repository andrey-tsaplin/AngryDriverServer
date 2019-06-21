//
// Created by andrew on 2/22/17.
//

#pragma once

#include <vector>
#include "rapidjson/writer.h"
#include "Player.h"

static const int DEFAULT_MAX_PLAYERS = 32;
static const int DEFAULT_MAX_OBJECTS = 1024;

class Level
{

protected:
    std::string name_;
    std::vector<Object *> objects_;
    std::vector<Player *> players_;
    b2World *world_;
    Engine *engine_;
    int maxPlayers_ = DEFAULT_MAX_PLAYERS;
    int maxObjects_ = DEFAULT_MAX_OBJECTS;

public:
    explicit Level(Engine *engine);

    virtual void Start();

    virtual void Step(double deltaTime);

    virtual bool AddObject(Object *object);

    virtual bool AddPlayer(Player *player);

    virtual std::vector<Player *> GetPlayers();

    virtual void ToJson(rapidjson::Document &json) const;

    virtual ~Level();
};
