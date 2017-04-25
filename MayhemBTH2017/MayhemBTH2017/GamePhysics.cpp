#include "GamePhysics.h"
#include "AProjectile.h"
#include "Game.h"




GamePhysics::GamePhysics()
{
}

GamePhysics::~GamePhysics()
{
}

void GamePhysics::enterWorld()
{

	//Get deltatime
	m_time = TimeManager::Get();
	b2Vec2 gravity(0.0f,- 0.3f);

	m_world = std::make_unique<b2World>(gravity);

	m_collision.CreateBoundingBoxes(m_world.get());

	//Set spawn position of player AND SIZE OF SPRITE BOX
	//PLAYER

	m_player = Player(m_world.get(), glm::vec2(0, 0), glm::vec2(1, 1));

	
}

void GamePhysics::Update(Transform transform)
{


	m_world->Step(1.0f / 60.0f, 6, 2);
	m_player.Update();
	//Check if player is in air 
	m_world->Step(1.0f / 60.0f, 6, 2);


}

glm::vec3 GamePhysics::GetPosition() {

	return m_transform.GetPosition();

}

void GamePhysics::Render(Transform &transform, Camera camera) {

	m_transform.SetPosition(42.0, 24.0, -0.0);
	m_transform.SetPosition(glm::vec3(m_player.GetPosition().x+0.854, m_player.GetPosition().y+0.42, 1));

	m_player.Render(m_transform, camera);
	glUseProgram(0);
	
}