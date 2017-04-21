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
	b2Vec2 gravity(0.0f, -9.81f);

	m_world = std::make_unique<b2World>(gravity);

	m_collision.CreateBoundingBoxes(m_world.get());

	//Set spawn position of player AND SIZE OF BOUNDING BOX
	m_player.Init(m_world.get(), glm::vec2(42, 24), glm::vec2(1.0, 1.0));

	m_playerSprite.createSprite(glm::vec2(0, 0), glm::vec2(1.0, 1.0));
	b2MassData* playerMass;
	m_player.GetBox().getFixture()->SetDensity(1.0);
	m_player.GetBox().getFixture()->SetFriction(0.3);
	m_player.GetBox().getFixture()->SetRestitution(0.2);


}

void GamePhysics::Update(Transform transform)
{



	m_tempX = m_player.GetBox().getBody()->GetPosition().x - (m_player.GetBox().getScale().x / 2);
	m_tempY = m_player.GetBox().getBody()->GetPosition().y - (m_player.GetBox().getScale().y / 2);
	m_scaleX = m_player.GetBox().getScale().x;
	m_scaleY = m_player.GetBox().getScale().y;


	m_playerSprite.update(glm::vec2(m_tempX, m_tempY), glm::vec2(m_scaleX, m_scaleY));

	m_world->Step(1.0f / 60.0f, 6, 2);
	b2Vec2 maxVel(-1990.01, 0);

	//controller input///////////////////////////////////////////
	

	void* bodyUserData = m_player.GetBox().getFixture()->GetBody()->GetUserData();
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTY) != 0.0f || InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX) != 0.0f)
	{
		m_player.GetBox().getBody()->SetLinearVelocity(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*(-600)*m_time->GetDeltaTime(), 0));

		transform.SetPosition(glm::vec3(-2.0f, 0.0, 0.0));

	}

	//Right stick


	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTY) != 0.0f || InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) != 0.0f)
	{

		m_player.GetBox().getBody()->SetLinearVelocity(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*(-600)*m_time->GetDeltaTime(), 0));

	}


	if (InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) != 0.0f)
	{
		std::cout << "JUMP" << std::endl;
		m_player.GetBox().getBody()->ApplyForce(b2Vec2(0, (1550000)*m_time->GetDeltaTime()), m_collision.GetBoxes()[m_collision.GetBoxes().size() - 1].getBody()->GetWorldCenter(), 1);

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
	m_playerSprite.draw();

	m_player.Render(transform, camera);
}