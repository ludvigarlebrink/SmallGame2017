#include "Box.h"



Box::Box()
{
}


Box::~Box()
{
}

void Box::initDynamic(b2World * world, const glm::vec2 & pos, const glm::vec2 & scale)
{
	this->m_scale = scale;


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);

	this->body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(scale.x / 2, scale.y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;

	this->fixture = this->body->CreateFixture(&fixtureDef);

}

void Box::initStatic(b2World * world, const glm::vec2 & pos, const glm::vec2 & scale)
{
	this->m_scale = scale;


	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pos.x + (scale.x/2), pos.y + (scale.y / 2));

	this->body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(scale.x / 2, scale.y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 0.4f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.7f;

	this->fixture = this->body->CreateFixture(&fixtureDef);
}


