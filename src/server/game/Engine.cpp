//
// Created by andrew on 2/22/17.
//

#include "Engine.h"
#include "../utils/Logger.h"

Engine::Engine(float replicationInterval)
{
    currentLevel_ = new Level(this);
    replicationInterval_ = replicationInterval;
}

bool Engine::IsDebug()
{
    return debug_;
}

void Engine::AddClient(Client *client)
{
    Logger::Verbose("[Engine] AddClient");
    Player *pl = new Player(client, this, currentLevel_);
    currentLevel_->AddPlayer(pl);
}

void Engine::Step(double deltaTime)
{
    currentLevel_->Step(deltaTime);

    timeToReplicate_ -= deltaTime;
    if(timeToReplicate_ < 0) {
        ReplicateState();
        timeToReplicate_ = replicationInterval_;
    }
}

void Engine::ReplicateState()
{
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
    for(auto player = players.begin(); player != players.end(); player++){
        (*player)->SendLevel(levelSerialized);
    }
}


