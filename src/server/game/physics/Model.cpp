//
// Created by andrew on 2/24/17.
//

#include "Model.h"
#include <math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

void Model::ToJson(rapidjson::Document &json) const
{
    using namespace rapidjson;
    Value shapes(kArrayType);

    for (auto body_iter = bodies_.begin(); body_iter != bodies_.end(); ++body_iter)
    {
        b2Transform transform = (*body_iter)->GetTransform();
        b2Fixture *fixture = (*body_iter)->GetFixtureList();
        for (; fixture; fixture = fixture->GetNext())
        {
            Value shapeJson(kObjectType);
            b2Shape *shape = fixture->GetShape();

            /*JSON API: t stands for shape type*/
            shapeJson.AddMember("t", Value().SetInt(shape->m_type), json.GetAllocator());

            if (shape->m_type == b2Shape::e_circle)
            {
                /*JSON API: v stands for circle shape radius*/
                shapeJson.AddMember("r", Value().SetFloat(((b2CircleShape *) shape)->m_radius), json.GetAllocator());
            }
            else if (shape->m_type == b2Shape::e_polygon)
            {
                Value vertices(kArrayType);
                b2PolygonShape *polygonShape = ((b2PolygonShape *) shape);

                for (int i = 0; i < polygonShape->m_count; i++)
                {
                    b2Vec2 pos = b2Mul(transform, polygonShape->GetVertex(i));
                    vertices.PushBack(trunc(pos.x * 10), json.GetAllocator());
                    vertices.PushBack(trunc(pos.y * 10), json.GetAllocator());
                }

                /*JSON API: v stands for poly shape vertices array*/
                shapeJson.AddMember("v", vertices, json.GetAllocator());
            }

            shapes.PushBack(shapeJson, json.GetAllocator());
        }
    }

    /*JSON API: s stands for shapes array*/
    json.AddMember("s", shapes, json.GetAllocator());
}

std::vector<b2Body *> Model::GetBodies()
{
    return bodies_;
}
