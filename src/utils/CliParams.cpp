//
// Created by andrew on 6/22/19.
//

#include "CliParams.h"
#include "Logger.h"

CliParameters CliParams::ReadCLIParameters(int argc, char **argv)
{
    auto parameters = CliParameters();

    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "--fps") == 0 || strcmp(argv[i], "-f") == 0)
        {
            parameters.fps = std::stoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--netRate") == 0 || strcmp(argv[i], "-n") == 0)
        {
            parameters.netRate = std::stoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--port") == 0 || strcmp(argv[i], "-p") == 0)
        {
            parameters.port = std::stoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0)
        {
            parameters.verbose = true;
        }
        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            parameters.printHelp = true;
        }
    }

    return parameters;
}

void CliParams::PrintHelp()
{
    Logger::Log(Logger::ERROR, "Usage: \n"
                               "angryDriverServer [OPTIONS]\n"
                               "Starts angry drivers game server\n\n"

                               "Supported OPTIONS are:\n"
                               "  -f, --fps          run server at specific FPS, default is 60\n"
                               "  -n, --netRate      network replication rate\n"
                               "  -p, --port         run on specific port, default is 8080\n"
                               "  -v, --verbose      verbose logging\n"
                               "  -h, --help         print this help\n"
                               "\n", false);
}