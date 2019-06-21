//
// Created by andrew on 6/22/19.
//

#include "TestLevel.h"
#include "Logger.h"

TestLevel::TestLevel(Engine *engine) : Level(engine)
{
    name_ = "TestLevel";
}

void TestLevel::Start()
{
    Level::Start();

    for(int i = 0; i < 5; i ++) {
        for(int j = 0; j < 5; j ++)
        {
            auto *box = new PhysicsObject(new Box(7.0, 7.0, true), engine_, this);
            box->Spawn(world_, b2Vec2(50 + 20 * i, 50 + 20 * j));
            AddObject(box);
        }
    }
}


