//
// Created by andrew on 3/1/17.
//

#pragma once

struct CliParameters
{
    int fps = 60;
    int netRate = 25;
    int port = 8080;
    bool printHelp = false;
    bool verbose = false;
};

namespace CliParams {
    CliParameters ReadCLIParameters(int argc, char **argv);
    void PrintHelp();
}
