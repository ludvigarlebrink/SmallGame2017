#include "Box.h"



Box::Box()
{
}


Box::~Box()
{
}

void Box::InitDynamic(b2World * world, const glm::vec2 & pos, const glm::vec2 & scale)
{
	m_scale = scale;


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);

	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(scale.x / 2, scale.y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;

	m_fixture = m_body->CreateFixture(&fixtureDef);

}

void Box::InitStatic(b2World * world, const glm::vec2 & pos, const glm::vec2 & scale)
{
	m_scale = scale;


	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pos.x + (scale.x/2), pos.y + (scale.y / 2));

	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(scale.x / 2, scale.y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 0.4f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.7f;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}

void Box::SetCategoryBits(short CATEGORY)
{
	m_fixtureDef.filter.categoryBits = CATEGORY;
}

void Box::SetMaskBits(short MASK)
{
	m_fixtureDef.filter.maskBits = MASK;
}

uint16 Box::GetCategoryBits()
{
	return m_fixtureDef.filter.categoryBits;
}

uint16 Box::GetMaskBits()
{
	return  m_fixtureDef.filter.maskBits;
}


