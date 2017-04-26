#include "Player.h"

//::..CONSTRUCTORS..:://
Player::Player(b2World* world, glm::vec2 pos, glm::vec2 scale) {

	Init(world, pos, scale);
}

Player::Player()
{

}


Player::~Player()
{
}
//::..INITIALIZERS..:://
void Player::Init(b2World* world, glm::vec2 pos, glm::vec2 scale)
{
	//Initiate the players bounding box
	m_boundingBox.initDynamic(world, pos, scale);

	//Load player MESH

	m_playerPrefab = PrefabManager::Instantiate("Player");



	//Load player shader
	//m_shader.Init(".\\Assets\\GLSL\\ToonShader", 0, 0);

	GetBox().getFixture()->SetDensity(1.0);
	GetBox().getFixture()->SetFriction(1.0);
	GetBox().getFixture()->SetRestitution(0.0);
	GetBox().getBody()->SetLinearDamping(0.2);

	//Set fixture 

}

void Player::Update() {

	if (GetBox().getBody()->GetLinearVelocity().y != 0) {
		m_isMidAir = true;
	}
	else {
		m_isMidAir = false;
	}


	//controller input///////////////////////////////////////////




	//LEFT MOVEMENT
	GLfloat leftVelocity = GetBox().getBody()->GetLinearVelocity().x*InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX);
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX) != 0.0f &&leftVelocity > -5)
	{

		if (m_isMidAir) {

			GetBox().getBody()->ApplyForce(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*(-500)*TimeManager::Get()->GetDeltaTime(), 0), GetBox().getBody()->GetWorldCenter(), 1);

		}
		if (!m_isMidAir && InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) == 0.0f) {

			GetBox().getBody()->SetLinearVelocity(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*(-350)*TimeManager::Get()->GetDeltaTime(), 0));
		}


	}

	GLfloat rightVelocity = GetBox().getBody()->GetLinearVelocity().x*InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX);

	//RIGHT MOVEMENT
	if (InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) != 0.0f &&rightVelocity > -5)
	{


		if (m_isMidAir) {

			GetBox().getBody()->ApplyForce(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX)*(-500)*TimeManager::Get()->GetDeltaTime(), 0), GetBox().getBody()->GetWorldCenter(), 1);
		}
		if (!m_isMidAir &&InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) == 0.0f) {

			GetBox().getBody()->SetLinearVelocity(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_RIGHTX)*(-350)*TimeManager::Get()->GetDeltaTime(), 0));
		}
	}


	if (InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) != 0.0f &&leftVelocity > -5 && rightVelocity > -5)
	{

		if (!m_isMidAir) {
			m_jumpTimer += 0.2f;
			std::cout << m_jumpTimer << std::endl;
			GetBox().getBody()->ApplyForce(b2Vec2(0, 500.0), GetBox().getBody()->GetWorldCenter(), 1);
			if (m_jumpTimer > 1.0f) {
				GetBox().getBody()->ApplyForce(b2Vec2(0, 500.0), GetBox().getBody()->GetWorldCenter(), 1);
			}
			//m_player.GetBox().getBody()->ApplyLinearImpulse(b2Vec2(0, impulse), m_player.GetBox().getBody()->GetWorldCenter(), 1);
		}
	}
	m_playerPrefab->SetPosition(glm::vec3(GetBox().getBody()->GetPosition().x, GetBox().getBody()->GetPosition().y, 1));


	//////////////////////////////////////////////////////////
	m_jumpTimer = 0.0f;

}

//::.. RENDER ..:://
void Player::Render(Camera camera) {

	m_playerPrefab->Render(camera);

}
Box Player::GetBox()
{
	return m_boundingBox;
}



//::.. SET FUNCTIONS ..:://
void Player::SetCategoryBits(short CATEGORY) {

	m_fixture.filter.categoryBits = CATEGORY;
}
void Player::SetMaskBits(short MASK) {

	m_fixture.filter.maskBits = MASK;

}

//::.. GET FUNCTIONS ..:://
uint16 Player::GetCategoryBits() {
	return m_fixture.filter.categoryBits;
}

uint16 Player::GetMaskBits() {

	return m_fixture.filter.maskBits;
}