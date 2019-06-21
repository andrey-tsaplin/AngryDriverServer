//
// Created by andrew on 2/22/17.
//

#pragma once

#include "Level.h"
#include "Logger.h"
#include "CliParams.h"
#include "GameLoopCounter.h"
#include "../transport/Client.h"

class WSServer;

class Engine
{
protected:
    CliParameters parameters_;
    WSServer* server_;
    GameLoopCounter counter_;
    Level *currentLevel_ = nullptr;
    float timeToReplicate_ = 0;
    bool isRunning_ = false;

public:
    explicit Engine(const CliParameters &parameters);

    void Initialize();

    void GameLoop();

    void ChangeLevel(Level* level);

    void StopLoop();

    bool AddClient(Client *client);

    void ReplicateState();
};
