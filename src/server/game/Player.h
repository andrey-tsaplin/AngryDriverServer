//
// Created by andrew on 3/2/17.
//

#pragma once

#include "../transport/Client.h"
#include "PhysicsObject.h"
#include "physics/Box.h"
#include "physics/car/CarBody.h"

class Engine;
class Level;

/* Player controller. Controls a car */
class Player
{
private:
    Client *client_;
    CarBody *car;
    Engine *engine_;
    Level *level_;

public:
    Player(Client *client, Engine *engine, Level *level);

    void Spawn(b2World *world);

    void Step(double deltaTime);

    void SendLevel(std::string &levelSerialized);
};
