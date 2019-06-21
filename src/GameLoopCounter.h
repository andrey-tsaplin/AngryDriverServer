//
// Created by andrew on 3/1/17.
//

#pragma once

struct GameLoopCounter {
    double totalTime = 0.;
    long totalCount = 0;

    void Print() {
        Logger::Verbose("Average iteration time is: %f ms", totalTime / totalCount);
    };

    void Reset() {
        totalTime = 0.;
        totalCount = 0;
    };

    void Count(double timeMs) {
        totalTime += timeMs;
        totalCount ++;
    }
};