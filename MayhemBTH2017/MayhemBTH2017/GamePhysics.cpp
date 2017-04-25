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
	b2Vec2 gravity(0.0f, -2.8f);

	m_world = std::make_unique<b2World>(gravity);

	m_collision.CreateBoundingBoxes(m_world.get());

	//Set spawn position of player AND SIZE OF SPRITE BOX
	//PLAYER
	m_player.Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0, 2.0));
	m_playerSprite.Init(".\\Assets\\GLSL\\ColliderShader", false, false);
	m_playerSprite.createSprite(glm::vec2(0, 0), glm::vec2(1.0, 1.0));

	m_player.GetBox().getFixture()->SetDensity(1.0);
	m_player.GetBox().getFixture()->SetFriction(0.5);
	m_player.GetBox().getFixture()->SetRestitution(0.0);
	m_player.GetBox().getBody()->SetLinearDamping(0);



}

void GamePhysics::Update(Transform transform)
{

	//Check if player is in air 


	m_scaleX = m_player.GetBox().getScale().x;
	m_scaleY = m_player.GetBox().getScale().y;
	m_tempX = m_player.GetBox().getBody()->GetPosition().x - (m_player.GetBox().getScale().x / 2);
	m_tempY = m_player.GetBox().getBody()->GetPosition().y - (m_player.GetBox().getScale().y / 2);

	//friction


	m_player.GetBox().getFixture()->SetFriction(0.5);



	m_playerSprite.update(glm::vec2(m_tempX, m_tempY), glm::vec2(m_scaleX, m_scaleY));



	m_world->Step(1.0f / 60.0f, 6, 2);
	b2Vec2 maxVel(-1990.01, 0);

	m_player.Update();

	m_world->Step(1.0f / 60.0f, 6, 2);

}

glm::vec3 GamePhysics::GetPosition() {

	return m_transform.GetPosition();

}

void GamePhysics::Render(Transform &transform, Camera camera) {


	m_transform.SetPosition(glm::vec3(m_tempX, m_tempY, 0));
	transform.SetPosition(glm::vec3(m_tempX, m_tempY, 0));

	m_collision.DrawCollider(camera);
	m_playerSprite.draw();

	m_player.Render(transform, camera);
}