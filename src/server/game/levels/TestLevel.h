//
// Created by andrew on 2/22/17.
//

#pragma once

#include "../Level.h"

class TestLevel : public Level
{
public:
    explicit TestLevel(Engine *engine);

    void Start() override;
};
