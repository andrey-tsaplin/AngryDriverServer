//
// Created by andrew on 2/22/17.
//

#pragma once

#include "../transport/Client.h"
#include "Level.h"

class Engine
{
protected:
    bool debug_ = false;
    Level *currentLevel_;

    float timeToReplicate_ = 0;
    float replicationInterval_ = 0;

public:
    Engine(float replicationInterval);

    bool IsDebug();

    void AddClient(Client *client);

    void Step(double deltaTime);

    void ReplicateState();
};
