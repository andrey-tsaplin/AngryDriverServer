//
// Created by andrew on 2/22/17.
//

#pragma once

#include "rapidjson/writer.h"
#include <vector>
#include "Player.h"

class Level
{
protected:
    std::string name_;
    std::vector<Object *> objects_;
    std::vector<Player *> players_;
    b2World world = b2World(b2Vec2(0, 0));
    Engine *engine_;

public:
    Level(Engine *engine);

    virtual void AddObject(Object *object);

    virtual void AddPlayer(Player *player);

    virtual std::vector<Player *> GetPlayers();

    virtual void Step(double deltaTime);

    virtual void ToJson(rapidjson::Document &json) const;
};
