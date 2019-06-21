#include <iostream>
#include <chrono>
#include <thread>
#include "libwebsockets.h"
#include "CliParams.h"
#include "GameLoopCounter.h"
#include "server/utils/Logger.h"
#include "server/transport/WSServer.h"

using namespace std::chrono;
typedef std::chrono::duration<double, std::milli> Milliseconds;

void GameLoop(CliParameters params) {
    Milliseconds frameTime(1000.0 / params.fps);

    Engine engine(1. / params.netRate);
    WSServer server(params.port, &engine);
    GameLoopCounter counter = GameLoopCounter();
    while (1)
    {
        auto frameStart = high_resolution_clock::now();

        /*Read users's input*/
        server.Service();

        /*Do engine step*/
        engine.Step(frameTime.count() / 1000.);

        /*Count and print stats*/
        Milliseconds timeElapsed = high_resolution_clock::now() - frameStart;
        counter.Count(timeElapsed.count());
        if (counter.totalCount == 100)
        {
            counter.Print();
            counter.Reset();
        }

        /*Sleep between before next frame*/
        auto sleepTime = frameTime - timeElapsed;
        std::this_thread::sleep_for(sleepTime);
    }
}

int main(int argc, char **argv)
{
    CliParameters params = ReadCLIParameters(argc, argv);
    if (params.printHelp)
    {
        PrintHelp();
        return 0;
    }

    Logger::SetLogLevel(params.verbose ? Logger::VERBOSE : Logger::WARNING);

    /*All the work is here*/
    GameLoop(params);
}


#pragma clang diagnostic pop