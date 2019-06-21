//
// Created by andrew on 3/2/17.
//

#include "Box.h"

Box::Box(float width, float height, bool dynamic)
{
    width_ = width;
    height_ = height;
    dynamic_ = dynamic;
}

void Box::Spawn(b2World *world, b2Vec2 position)
{
    b2BodyDef boxDef;
    boxDef.type = dynamic_ ? b2_dynamicBody : b2_staticBody;
    boxDef.position.x = position.x;
    boxDef.position.y = position.y;

    b2Body *boxBody = world->CreateBody(&boxDef);

    b2PolygonShape *boxShape = new b2PolygonShape();
    boxShape->SetAsBox(width_ / 2, height_ / 2);

    b2FixtureDef *boxFixture = new b2FixtureDef();
    boxFixture->shape = boxShape;
    boxFixture->density = DEFAULT_DENSITY;
    boxFixture->restitution = DEFAULT_RESTITUTION;
    boxFixture->friction = DEFAULT_FRICTION;
    boxBody->CreateFixture(boxFixture);

    bodies_.push_back(boxBody);
}

void Box::Destroy(b2World *world)

{
    for (auto iter = bodies_.begin(); iter != bodies_.end(); iter++)
    {
        world->DestroyBody((*iter));
    }
}
