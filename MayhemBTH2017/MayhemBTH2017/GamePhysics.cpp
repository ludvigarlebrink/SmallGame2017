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
	m_player.Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0, 3.0));
	m_playerSprite.Init(".\\Assets\\GLSL\\ColliderShader", false, false);
	m_playerSprite.createSprite(glm::vec2(0, 0), glm::vec2(1.0, 1.0));
	///////////////////////////////////////////////////////////////////

	//Power up

	m_powerUpBox.initDynamic(m_world.get(), glm::vec2(42,24), glm::vec2(2.0, 3.0));
	m_powerUpSprite.Init(".\\Assets\\GLSL\\PowerUpShader", false, false);
	m_powerUpSprite.createSprite(glm::vec2(0, 0), glm::vec2(1.0, 1.0));

	m_powerUpBox.getFixture()->SetDensity(1.0);
	m_powerUpBox.getFixture()->SetFriction(1.0);
	m_powerUpBox.getFixture()->SetRestitution(0.0);
	m_powerUpBox.getBody()->SetLinearDamping(0.2);
	///////////////////////////////////////////////////////////////////

}

void GamePhysics::Update(Transform transform)
{

	//Update player bounding box sprite position to the position of the player mesh
	m_playerScaleX = m_player.GetBox().getScale().x;
	m_playerScaleY = m_player.GetBox().getScale().y;
	m_playerPosX = m_player.GetBox().getBody()->GetPosition().x - (m_player.GetBox().getScale().x / 2);
	m_playerPosY = m_player.GetBox().getBody()->GetPosition().y - (m_player.GetBox().getScale().y / 2);

	m_playerSprite.update(glm::vec2(m_playerPosX +0.42, m_playerPosY + 0.24), glm::vec2(m_playerScaleX- 0.84, m_playerScaleY - 0.48));

	//Update powerUp bounding box sprite position to the position of the player mesh
	m_powerUpScaleX = m_powerUpBox.getScale().x;
	m_powerUpScaleY = m_powerUpBox.getScale().y;
	m_powerUpPosX = m_powerUpBox.getBody()->GetPosition().x - (m_player.GetBox().getScale().x / 2);
	m_powerUpPosY = m_powerUpBox.getBody()->GetPosition().y - (m_player.GetBox().getScale().y / 2);

	m_powerUpSprite.update(glm::vec2(m_powerUpPosX-0.42, m_powerUpPosY + 0.24), glm::vec2(m_powerUpScaleX+0.84, m_powerUpScaleY - 0.48));




	m_world->Step(1.0f / 60.0f, 6, 2);



	m_player.Update();

	m_world->Step(1.0f / 60.0f, 6, 2);

}

glm::vec3 GamePhysics::GetPosition() {

	return m_transform.GetPosition();

}

void GamePhysics::Render(Transform &transform, Camera camera) {

	m_transform.SetPosition(glm::vec3(m_playerPosX, m_playerPosY, 0));
	camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));

	m_collision.DrawCollider(camera);

	//player sprite
	m_playerSprite.Bind();
	m_playerSprite.Update(transform, camera);
	m_playerSprite.draw();

	glUseProgram(0);

	m_powerUpSprite.Bind();
	m_powerUpSprite.Update(transform, camera);
	m_powerUpSprite.draw();

	//m_player.Render(transform, camera);
}