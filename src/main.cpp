#include <iostream>
#include <chrono>
#include <thread>
#include "libwebsockets.h"
#include "Logger.h"
#include "CliParams.h"
#include "server/game/Engine.h"
#include "server/game/levels/TestLevel.h"

int main(int argc, char **argv)
{
    CliParameters params = CliParams::ReadCLIParameters(argc, argv);
    if (params.printHelp)
    {
        CliParams::PrintHelp();
        return 0;
    }

    Logger::SetLogLevel(params.verbose ? Logger::VERBOSE : Logger::WARNING);

    Logger::Verbose("[main] Starting engine");
    Engine engine(params);
    engine.Initialize();
    engine.ChangeLevel(new TestLevel(&engine));

    Logger::Verbose("[main] Starting game loop");
    engine.GameLoop();
    Logger::Verbose("[main] Engine stopped");
}