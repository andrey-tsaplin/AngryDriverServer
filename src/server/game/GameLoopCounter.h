//
// Created by andrew on 3/1/17.
//

#pragma once

#include "Logger.h"

struct GameLoopCounter {
    double totalTime = 0.;
    long totalCount = 0;

    void Print() {
        Logger::Verbose("Average iteration time is: %f ms", totalTime * 1000 / totalCount);
    };

    void Reset() {
        totalTime = 0.;
        totalCount = 0;
    };

    void Count(double time) {
        totalTime += time;
        totalCount ++;
    }
};