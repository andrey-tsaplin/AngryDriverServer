//
// Created by andrew on 2/22/17.
//

#pragma once

#include <vector>
#include "Object.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include "physics/Model.h"

class PhysicsObject : public Object
{
protected:
	Model *model_;

public:
	PhysicsObject(Model *model, Engine *engine, Level *level, int type = GAME_OBJECT_PHYSICS);

	Model *GetModel();

	virtual void Step(double deltaTime);

	virtual void ToJson(rapidjson::Document &json) const;

	virtual void Spawn(b2World *world, b2Vec2 position);

	virtual void Destroy(b2World *world);

};
