#include "Box.h"



Box::Box()
{
}


Box::~Box()
{
}

void Box::init(b2World * world, const glm::vec2 & pos, const glm::vec2 & scale)
{
	this->m_scale = scale;

	this->sprite;

	this->sprite.Init("leo", false, false);


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);

	this->body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(scale.x / 2, scale.y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 0.4f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.7f;

	this->fixture = this->body->CreateFixture(&fixtureDef);

	this->sprite.createSprite(pos, scale);

}

void Box::setTexture(const std::string & filePath)
{
	this->sprite.setTexture(filePath);
}

void Box::draw()
{
	//this->body->ApplyForce(b2Vec2(0.2f, 0.1f), b2Vec2(0.1f, 0.1f), true);

	this->sprite.draw();
}

void Box::updateSprite(glm::vec2 pos, glm::vec2 scale)
{
	this->sprite.update(pos, scale);
}

