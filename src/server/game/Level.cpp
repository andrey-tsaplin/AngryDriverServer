//
// Created by andrew on 2/22/17.
//

#include "Level.h"

Level::Level(Engine* engine) {
    name_ = "BasicLevel";
    engine_ = engine;

    /* constructs empty physics box around level */
    PhysicsObject* bottom = new PhysicsObject(new Box(1000.0, 1.0, false), engine_, this);
    bottom->Spawn(&world, b2Vec2(0, 250));
    AddObject(bottom);

    PhysicsObject* top = new PhysicsObject(new Box(1000.0, 1.0, false), engine_, this);
    top->Spawn(&world, b2Vec2(0, 0));
    AddObject(top);

    PhysicsObject* left = new PhysicsObject(new Box(1.0, 1000.0, false), engine_, this);
    left->Spawn(&world, b2Vec2(0, 0));
    AddObject(left);

    PhysicsObject* right = new PhysicsObject(new Box(1.0, 1000.0, false), engine_, this);
    right->Spawn(&world, b2Vec2(400, 0));
    AddObject(right);

    /*Just for fun*/
    for(int i = 0; i < 5; i ++) {
        for(int j = 0; j < 5; j ++)
        {
            PhysicsObject *box = new PhysicsObject(new Box(7.0, 7.0, true), engine_, this);
            box->Spawn(&world, b2Vec2(50 + 20 * i, 50 + 20 * j));
            AddObject(box);
        }
    }
}

void Level::Step(double deltaTime) {
    for(auto player = players_.begin(); player != players_.end(); player++){
        (*player)->Step(deltaTime);
    }

    for(auto object = objects_.begin(); object != objects_.end(); object++){
        (*object)->Step(deltaTime);
    }

    world.Step(deltaTime, 3, 3);
}


void Level::ToJson(rapidjson::Document &json) const {
    using namespace rapidjson;

    //JSON API: n stands for level name
    json.AddMember("n", Value().SetString(name_, json.GetAllocator()), json.GetAllocator());

    Value objects(kArrayType);
    for(auto iter = objects_.begin(); iter != objects_.end(); iter++) {
        Document objectJson(kObjectType, &json.GetAllocator());
        (*iter)->ToJson(objectJson);
        objects.PushBack(objectJson, json.GetAllocator());
    }

    //JSON API: o stands for level objects
    json.AddMember("o", objects, json.GetAllocator());
}

void Level::AddPlayer(Player *player) {
    players_.push_back(player);
    player->Spawn(&world);
}

std::vector<Player *> Level::GetPlayers() {
    return players_;
}

void Level::AddObject(Object *object) {
    objects_.push_back(object);
}
