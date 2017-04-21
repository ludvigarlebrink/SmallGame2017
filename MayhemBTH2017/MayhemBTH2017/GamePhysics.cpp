#include "GamePhysics.h"
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
	b2Vec2 gravity(0.0f, -0.8f);

	m_world = std::make_unique<b2World>(gravity);

	m_collision.CreateBoundingBoxes(m_world.get());


	//Set spawn position of player AND SIZE OF SPRITE BOX
	//PLAYER
	m_player.Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0, 3.0));
	m_playerSprite.createSprite(glm::vec2(0, 0), glm::vec2(1.0, 1.0));

	m_player.GetBox().getFixture()->SetDensity(1.0);
	m_player.GetBox().getFixture()->SetFriction(1.0);
	m_player.GetBox().getFixture()->SetRestitution(0.0);



}

void GamePhysics::Update(Transform transform)
{

	//Check if player is in air 
	if (m_player.GetBox().getBody()->GetLinearVelocity().y != 0) {
		m_isMidAir = true;
	}
	else {
		m_isMidAir = false;
	}

	m_jumpTimer += 0.02f;
	if (m_jumpTimer > 10.0f) {
		m_jumpTimer = 10.0f;
	}

	m_scaleX = m_player.GetBox().getScale().x;
	m_scaleY = m_player.GetBox().getScale().y;
	m_tempX = m_player.GetBox().getBody()->GetPosition().x - (m_player.GetBox().getScale().x / 2);
	m_tempY = m_player.GetBox().getBody()->GetPosition().y - (m_player.GetBox().getScale().y / 2);

	//friction
	
	
	m_player.GetBox().getFixture()->SetFriction(0.5);



	m_playerSprite.update(glm::vec2(m_tempX, m_tempY), glm::vec2(m_scaleX, m_scaleY));

	

	m_world->Step(1.0f / 60.0f, 6, 2);
	b2Vec2 maxVel(-1990.01, 0);

	//controller input///////////////////////////////////////////


	void* bodyUserData = m_player.GetBox().getFixture()->GetBody()->GetUserData();

	//LEFT MOVEMENT
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTY) != 0.0f || InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX) != 0.0f)
	{
		if (m_isMidAir) {
			m_player.GetBox().getBody()->ApplyLinearImpulse(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*(-20)*m_time->GetDeltaTime(), 0), m_player.GetBox().getBody()->GetWorldCenter(), 1);
		}
		if (!m_isMidAir) {
			m_player.GetBox().getBody()->ApplyLinearImpulse(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*(-40)*m_time->GetDeltaTime(), 0), m_player.GetBox().getBody()->GetWorldCenter(), 1);
		}


	}


	//RIGHT MOVEMENT
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTY) != 0.0f || InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) != 0.0f)
	{

		if (m_isMidAir) {
			m_player.GetBox().getBody()->ApplyLinearImpulse(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX)*(-20)*m_time->GetDeltaTime(), 0), m_player.GetBox().getBody()->GetWorldCenter(), 1);
		}
		if (!m_isMidAir) {
			m_player.GetBox().getBody()->ApplyLinearImpulse(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX)*(-40)*m_time->GetDeltaTime(), 0), m_player.GetBox().getBody()->GetWorldCenter(), 1);
		}
	}


	if (InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) != 0.0f)
	{
		std::cout << "JUMP" << std::endl;
	
		if (!m_isMidAir) {
			m_player.GetBox().getBody()->ApplyForce(b2Vec2(0, 180.5), m_player.GetBox().getBody()->GetWorldCenter(), 1);
			//m_player.GetBox().getBody()->ApplyLinearImpulse(b2Vec2(0, impulse), m_player.GetBox().getBody()->GetWorldCenter(), 1);
		}
	}
	//////////////////////////////////////////////////////////


	m_world->Step(1.0f / 60.0f, 6, 2);


}

glm::vec3 GamePhysics::GetPosition() {

	return m_transform.GetPosition();

}

void GamePhysics::Render(Transform &transform, Camera camera) {


	m_transform.SetPosition(glm::vec3(m_tempX, m_tempY, 0));
	transform.SetPosition(glm::vec3(m_tempX, m_tempY, 0));

	m_collision.DrawCollider(camera);
	//m_playerSprite.draw();

	m_player.Render(transform, camera);
}