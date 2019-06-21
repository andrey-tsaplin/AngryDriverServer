//
// Created by andrew on 2/22/17.
//

#include <chrono>
#include <thread>
#include "Engine.h"
#include "../transport/WSServer.h"

using namespace std::chrono;
typedef duration<double> Seconds;

Engine::Engine(const CliParameters &parameters) : parameters_(parameters)
{
    server_ = new WSServer();
}

void Engine::Initialize()
{
    server_->Listen(parameters_.port, this);
}

void Engine::GameLoop()
{
    if (isRunning_)
    {
        return;
    }
    isRunning_ = true;

    Seconds frameTime(1. / parameters_.fps);

    while (isRunning_)
    {
        auto frameStart = high_resolution_clock::now();

        /*Read users's input*/
        server_->Service();

        /*Do world step*/
        if (currentLevel_)
        {
            currentLevel_->Step(frameTime.count());
        }

        /*Replicate data*/
        timeToReplicate_ -= frameTime.count();
        if (timeToReplicate_ <= 0)
        {
            ReplicateState();
            timeToReplicate_ = 1.f / parameters_.netRate;
        }

        /*Count and print stats*/
        Seconds timeElapsed = high_resolution_clock::now() - frameStart;
        counter_.Count(timeElapsed.count());
        if (counter_.totalCount == 100)
        {
            counter_.Print();
            counter_.Reset();
        }

        /*Sleep between before next frame*/
        auto sleepTime = frameTime - timeElapsed;
        std::this_thread::sleep_for(sleepTime);
    }

    delete currentLevel_;
}

void Engine::StopLoop()
{
    isRunning_ = false;
}

void Engine::ChangeLevel(Level *level)
{
    delete currentLevel_;
    currentLevel_ = level;
    currentLevel_->Start();
}

bool Engine::AddClient(Client *client)
{
    if (!currentLevel_)
    {
        return false;
    }

    auto player = new Player(client, this, currentLevel_);
    bool isAdded = currentLevel_->AddPlayer(player);

    if (isAdded)
    {
        Logger::Verbose("[Engine] new player connected");
    } else
    {
        Logger::Verbose("[Engine] new player dropped");
    }

    return isAdded;
}

void Engine::ReplicateState()
{
    if(!currentLevel_) {
        return;
    }

    using namespace rapidjson;
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    /*Serialize level state*/
    Document levelJson(kObjectType);
    currentLevel_->ToJson(levelJson);
    levelJson.Accept(writer);
    std::string levelSerialized(buffer.GetString());

    /* Send it to every player */
    auto players = currentLevel_->GetPlayers();
    for (auto player : players)
    {
        player->SendLevel(levelSerialized);
    }
}

