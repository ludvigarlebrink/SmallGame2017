#include "Player.h"

Player::Player(b2World* world, glm::vec2 pos, glm::vec2 scale) {

	Init(world, pos, scale);
}



Player::Player() {

}

Player::~Player()
{
}



void Player::Init(b2World* world, glm::vec2 pos, glm::vec2 scale) {

	m_world = world;
	//Initiate the players bounding box
	m_boundingBox.initDynamic(world, pos, scale);

	//Load player MESH
	m_playerMesh = m_meshImp.Import();

	//Load player shader to draw our player character
	m_shader.Init(".\\Assets\\GLSL\\ToonShader", 0, 0);


	m_time = TimeManager::Get();

	//shader to draw our bounding box sprite for the player
	m_spriteShader.Init(".\\Assets\\GLSL\\ColliderShader", 0, 0);
	m_playerSprite.createSprite(glm::vec2(0, 0), glm::vec2(1.0, 1.0));

	GetBox().getFixture()->SetDensity(1.0);
	GetBox().getFixture()->SetFriction(1.0);
	GetBox().getFixture()->SetRestitution(0.0);
	GetBox().getBody()->SetLinearDamping(0.0);

}

void Player::Update() {


	if (GetBox().getBody()->GetLinearVelocity().y != 0) {
		m_isMidAir = true;

	}
	else {
		m_isMidAir = false;

	}
	m_scaleX = GetBox().getScale().x;
	m_scaleY = GetBox().getScale().y;
	m_posX = GetBox().getBody()->GetPosition().x - (GetBox().getScale().x / 2);
	m_posY = GetBox().getBody()->GetPosition().y - (GetBox().getScale().y / 2);

	m_playerSprite.update(glm::vec2(m_posX, m_posY), glm::vec2(m_scaleX, m_scaleY));

	//controller input///////////////////////////////////////////


	//LEFT MOVEMENT

	GLfloat leftVelocity = GetBox().getBody()->GetLinearVelocity().x*InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX);
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX) != 0.0f && leftVelocity > -3)
	{

		if (m_isMidAir) {

			GetBox().getBody()->ApplyLinearImpulse(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*(-3)*m_time->GetDeltaTime(), 0), GetBox().getBody()->GetWorldCenter(), 1);

		}
		if (!m_isMidAir &&InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) == 0.0f) {

			GetBox().getBody()->SetLinearVelocity(b2Vec2(-3 * InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX), 0));
		}


	}

	GLfloat rightVelocity = GetBox().getBody()->GetLinearVelocity().x*InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX);

	//RIGHT MOVEMENT
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) != 0.0f && rightVelocity > -3)
	{


		if (m_isMidAir) {

			GetBox().getBody()->ApplyLinearImpulse(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX)*(-3)*m_time->GetDeltaTime(), 0), GetBox().getBody()->GetWorldCenter(), 1);
		}
		if (!m_isMidAir &&InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) == 0.0f) {

			GetBox().getBody()->SetLinearVelocity(b2Vec2(3 * InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX), 0));
		}
	}


	if (InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) != 0.0f &&leftVelocity > -3 && rightVelocity > -3 && GetBox().getBody()->GetLinearVelocity().y < 1)
	{


		if (!m_isMidAir) {
			GetBox().getBody()->ApplyLinearImpulse(b2Vec2(0, 10.5), GetBox().getBody()->GetWorldCenter(), 1);
			GetBox().getFixture()->SetFriction(0.0);


		}
	}
	//////////////////////////////////////////////////////////

	//IF no AXIS moved
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) == 0.0f && InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX) == 0.0f && m_isMidAir == false && InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) == 0.0f) {
		GetBox().getBody()->SetLinearVelocity(b2Vec2(0, 0));

	}

	

	if (GetBox().getBody()->GetLinearVelocity().y > 0) {
		GetBox().getBody()->GetFixtureList()->SetSensor(true);

	}

	if (GetBox().getBody()->GetLinearVelocity().y <= 0) {
		GetBox().getBody()->GetFixtureList()->SetSensor(false);
	}


}

Box Player::GetBox()
{
	return m_boundingBox;
}


void Player::Render(Transform transform, Camera camera) {

	m_shader.Bind();
	m_shader.Update(transform, camera);
	m_playerMesh.Render();
	
	
	//m_transform.SetPosition(42.0, 24.0, -0.0);
	//
	//m_spriteShader.Bind();
	//m_spriteShader.Update(m_transform, camera);
	//m_playerSprite.draw();

}

glm::vec2 Player::GetPosition() {
	return glm::vec2(m_posX, m_posY);
}
glm::vec2 Player:: GetScale(){
	return glm::vec2(m_scaleX, m_scaleY);
}