#include "GamePhysics.h"



GamePhysics::GamePhysics()
{
}


GamePhysics::~GamePhysics()
{
}

void GamePhysics::EnterWorld()
{
	b2Vec2 gravity(0.0f, -9.81);

	m_world = std::make_unique<b2World>(gravity);


	//create ground
	b2BodyDef groundBodyDef;

	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
	// make ground fixture

	b2PolygonShape groundBox;

	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	newBox;

	newBox.Init(m_world.get(), glm::vec2(0.0f, 0.5f), glm::vec2(0.5f, 0.5f));

	
}

void GamePhysics::Update()
{
	m_world->Step(1.0f / 60.0f, 6, 2);

	newBox.update(glm::vec2(this->newBox.GetBody()->GetPosition().x, this->newBox.GetBody()->GetPosition().y));

	newBox.draw();

}
