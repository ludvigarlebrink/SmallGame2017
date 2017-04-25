#include "Player.h"

Player::Player(b2World* world, glm::vec2 pos, glm::vec2 scale) {
	
	Init(world, pos, scale);
}

Player::Player()
{

}


Player::~Player()
{
}

void Player::Init(b2World* world, glm::vec2 pos, glm::vec2 scale)
{
	//Initiate the players bounding box
	m_boundingBox.initDynamic(world, pos, scale);
	
	//Load player MESH
	m_playerMesh = m_meshImp.Import();

	//Load player shader
	m_shader.Init(".\\Assets\\GLSL\\ToonShader", 0, 0);

}

void Player::Update() {

	if (GetBox().getBody()->GetLinearVelocity().y != 0) {
		m_isMidAir = true;
	}
	else {
		m_isMidAir = false;
	}

	m_jumpTimer += 0.02f;
	if (m_jumpTimer > 10.0f) {
		m_jumpTimer = 10.0f;
	}

	//controller input///////////////////////////////////////////

	//LEFT MOVEMENT
	GLfloat leftVelocity = GetBox().getBody()->GetLinearVelocity().x*InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX);
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTY) != 0.0f || InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX) != 0.0f &&leftVelocity>-5)
	{
		std::cout << leftVelocity << std::endl;
		if (m_isMidAir) {

			GetBox().getBody()->ApplyLinearImpulse(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*(-5)*TimeManager::Get()->GetDeltaTime(), 0), GetBox().getBody()->GetWorldCenter(), 1);

		}
		if (!m_isMidAir &&InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) == 0.0f) {

			GetBox().getBody()->SetLinearVelocity(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*(-800)*TimeManager::Get()->GetDeltaTime(), 0));
		}


	}

	GLfloat rightVelocity = GetBox().getBody()->GetLinearVelocity().x*InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX);

	//RIGHT MOVEMENT
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTY) != 0.0f || InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) != 0.0f &&rightVelocity > -5)
	{


		if (m_isMidAir) {

			GetBox().getBody()->ApplyLinearImpulse(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX)*(-5)*TimeManager::Get()->GetDeltaTime(), 0), GetBox().getBody()->GetWorldCenter(), 1);
		}
		if (!m_isMidAir &&InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) == 0.0f) {

			GetBox().getBody()->SetLinearVelocity(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX)*(-800)*TimeManager::Get()->GetDeltaTime(), 0));
		}
	}


	if (InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) != 0.0f &&leftVelocity>-5 && rightVelocity > -5)
	{
		std::cout << "JUMP" << std::endl;

		if (!m_isMidAir) {
			GetBox().getBody()->ApplyLinearImpulse(b2Vec2(0, 10.5), GetBox().getBody()->GetWorldCenter(), 1);
			//m_player.GetBox().getBody()->ApplyLinearImpulse(b2Vec2(0, impulse), m_player.GetBox().getBody()->GetWorldCenter(), 1);
		}
	}
	//////////////////////////////////////////////////////////
	

}

Box Player::GetBox()
{
	return m_boundingBox;
}


void Player::Render(Transform transform, Camera camera) {
	
	m_shader.Bind();
	m_shader.Update(transform, camera);


	m_playerMesh.Render();

	glUseProgram(0);

}

