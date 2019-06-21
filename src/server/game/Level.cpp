//
// Created by andrew on 2/22/17.
//

#include "Logger.h"
#include "Level.h"

Level::Level(Engine* engine) {
    name_ = "DummyLevel";
    engine_ = engine;
}

void Level::Start()
{
    world_ = new b2World(b2Vec2(0, 0));

    /* constructs empty physics box around level */
    auto bottomWall = new PhysicsObject(new Box(1000.0, 1.0, false), engine_, this);
    bottomWall->Spawn(world_, b2Vec2(0, 250));
    AddObject(bottomWall);

    auto topWall = new PhysicsObject(new Box(1000.0, 1.0, false), engine_, this);
    topWall->Spawn(world_, b2Vec2(0, 0));
    AddObject(topWall);

    auto leftWall = new PhysicsObject(new Box(1.0, 1000.0, false), engine_, this);
    leftWall->Spawn(world_, b2Vec2(0, 0));
    AddObject(leftWall);

    auto rightWall = new PhysicsObject(new Box(1.0, 1000.0, false), engine_, this);
    rightWall->Spawn(world_, b2Vec2(400, 0));
    AddObject(rightWall);
}

void Level::Step(double deltaTime) {
    for (auto player : players_)
    {
        player->Step(deltaTime);
    }

    for (auto object : objects_)
    {
        object->Step(deltaTime);
    }

    world_->Step(deltaTime, 3, 3);
}


void Level::ToJson(rapidjson::Document &json) const {
    using namespace rapidjson;

    //JSON API: n stands for level name
    json.AddMember("n", Value().SetString(name_, json.GetAllocator()), json.GetAllocator());

    Value objects(kArrayType);
    for (auto object : objects_)
    {
        Document objectJson(kObjectType, &json.GetAllocator());
        object->ToJson(objectJson);
        objects.PushBack(objectJson, json.GetAllocator());
    }

    //JSON API: o stands for level objects
    json.AddMember("o", objects, json.GetAllocator());
}

bool Level::AddPlayer(Player *player) {
    if(players_.size() == maxPlayers_) {
        return false;
    }

    players_.push_back(player);
    player->Spawn(world_);
    return true;
}

std::vector<Player *> Level::GetPlayers() {
    return players_;
}

bool Level::AddObject(Object *object) {
    if(objects_.size() == maxObjects_) {
        return false;
    }

    objects_.push_back(object);
    return true;
}

Level::~Level()
{
    for(auto *obj : objects_) {
        delete obj;
    }

    delete world_;
}