//
// Created by andrew on 2/22/17.
//

#pragma once

#include <vector>
#include "Model.h"
#include "../Object.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>


class PhysicsObject : public Object
{
protected:
	Model *model_;

public:
	PhysicsObject(Model *model, Engine *engine, Level *level, int type = GAME_OBJECT_PHYSICS);

	Model *GetModel();

    void Step(double deltaTime) override;

    void ToJson(rapidjson::Document &json) const override;

	virtual void Spawn(b2World *world, b2Vec2 position);

	virtual void Destroy();

    ~PhysicsObject() override;

};
