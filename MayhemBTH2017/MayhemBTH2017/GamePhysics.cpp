#include "GamePhysics.h"



GamePhysics::GamePhysics()
{
}

GamePhysics::~GamePhysics()
{
}

void GamePhysics::enterWorld()
{
	b2Vec2 gravity(0.0f, -9.81f);

	m_world = std::make_unique<b2World>(gravity);

	b2BodyDef groundBodyDef;

	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;

	groundBox.SetAsBox(10.0f, 9.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	m_newBox.init(m_world.get(), glm::vec2(0.0, 1.0), glm::vec2(0.1, 0.2));

	m_newBox.setTexture("MARBLES.BMP");

	m_newBox2.init(m_world.get(), glm::vec2(-0.5, 1.0), glm::vec2(0.1, 0.2));

	m_newBox2.setTexture("MARBLES.BMP");

}

void GamePhysics::update()
{

	m_world->Step(1.0f / 60.0f, 6, 2);

	glm::vec4 destRect;
	destRect.x = m_newBox.getBody()->GetPosition().x;
	destRect.y = m_newBox.getBody()->GetPosition().y;
	destRect.z = m_newBox.getScale().x;
	destRect.w = m_newBox.getScale().y;

	m_newBox.updateSprite(glm::vec2(destRect.x, destRect.y), glm::vec2(destRect.z, destRect.w));

	m_newBox.draw();

	glm::vec4 destRect2;
	destRect2.x = m_newBox2.getBody()->GetPosition().x;
	destRect2.y = m_newBox2.getBody()->GetPosition().y;
	destRect2.z = m_newBox2.getScale().x;
	destRect2.w = m_newBox2.getScale().y;

	m_newBox2.updateSprite(glm::vec2(destRect2.x, destRect2.y), glm::vec2(destRect2.z, destRect2.w));

	m_newBox2.draw();

}
