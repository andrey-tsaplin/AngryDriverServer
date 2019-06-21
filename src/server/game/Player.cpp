//
// Created by andrew on 3/2/17.
//

#include "Player.h"

Player::Player(Client *client, Engine *engine, Level *level)
{
	client_ = client;
	engine_ = engine;
	level_ = level;
}

void Player::Step(double deltaTime)
{
	int controls = 0;

	if (client_->IsUpPressed())
	{
		controls |= TDC_UP;
	}
	else if (client_->IsDownPressed())
	{
		controls |= TDC_DOWN;
	}

	if (client_->IsLeftPressed())
	{
		controls |= TDC_LEFT;
	}
	else if (client_->IsRightPressed())
	{
		controls |= TDC_RIGHT;
	}

	car->SetControlState(controls);
}

void Player::Spawn(b2World *world)
{
	car = new CarBody();
	PhysicsObject *carObj = new PhysicsObject(car, engine_, level_);
	carObj->Spawn(world, b2Vec2(100, 100));
}

void Player::SendLevel(std::string &levelSerialized)
{
	client_->AddToMessageQueue(levelSerialized);
}
