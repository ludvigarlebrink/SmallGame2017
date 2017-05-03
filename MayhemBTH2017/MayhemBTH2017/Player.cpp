#include "Player.h"

//::..CONSTRUCTORS..:://
Player::Player(b2World* world, glm::vec2 pos, glm::vec2 scale) {

	Init(world, pos, scale);
	m_contact = false;
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
	m_contact = false;
	//Load player MESH

	m_playerPrefab = new PlayerPrefab();
	
	//m_playerPrefab->SetScale(glm::vec3(1.3));


	//SET BOUNDING BOX SIZE 
	m_boundingBox.InitDynamic(world, pos, glm::vec2(m_playerPrefab->GetPlayerPrefab()->GetScale().x + 1, m_playerPrefab->GetPlayerPrefab()->GetScale().y*m_playerPrefab->GetPlayerPrefab()->GetMesh()->GetHeight()));
	//sprite for size of bouding box
	m_playerSprite.createSprite(glm::vec2(0), glm::vec2(20));
	m_playerSprite.Init(".\\Assets\\GLSL\\ColliderShader", 0, 0);
	//Load player shader
	//m_shader.Init(".\\Assets\\GLSL\\ToonShader", 0, 0);

	GetBox().getFixture()->SetDensity(5.0);
	GetBox().getFixture()->SetFriction(1.0);
	GetBox().getFixture()->SetRestitution(0.0);
	GetBox().getBody()->SetLinearDamping(0.4);
	
	b2Filter filter;
	filter.categoryBits = PLAYER;
	filter.maskBits = BOUNDARY;
	GetBox().getFixture()->SetFilterData(filter);

	GetBox().getBody()->SetUserData(this);

	//Set fixture 

}

void Player::Update() {

	if (GetBox().getBody()->GetLinearVelocity().y != 0) {
		m_isMidAir = true;
	
		
	}
	else {
		m_isMidAir = false;
		m_doubleJump = false;
	}


	//controller input///////////////////////////////////////////




	//PLAYER MOVEMENT
	GLfloat leftVelocity = GetBox().getBody()->GetLinearVelocity().x*InputManager::Get()->GetAxis(CONTROLLER_AXIS_LEFT_X);
	
	if (InputManager::Get()->GetAxis(CONTROLLER_AXIS_LEFT_X) != 0.0f &&leftVelocity > -5)
	{
	//	m_playerPrefab->SetRotation(0, 90 * InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX), 0);
		if (m_isMidAir) {

			GetBox().getBody()->ApplyForce(b2Vec2(InputManager::Get()->GetAxis(CONTROLLER_AXIS_LEFT_X)*(-100)*TimeManager::Get()->GetDeltaTime(), 0), GetBox().getBody()->GetWorldCenter(), 1);

		}
		if (!m_isMidAir ) {

			GetBox().getBody()->SetLinearVelocity(b2Vec2(InputManager::Get()->GetAxis(CONTROLLER_AXIS_LEFT_X)*(-200)*TimeManager::Get()->GetDeltaTime(), 0));
		}


	}





	if (InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) != 0.0f)
	{
		

		if (!m_isMidAir) {

			//First jump
			GetBox().getBody()->ApplyForce(b2Vec2(0, 100), GetBox().getBody()->GetWorldCenter(), 1);
			m_doubleJump = true;
	


			//m_player.GetBox().getBody()->ApplyLinearImpulse(b2Vec2(0, impulse), m_player.GetBox().getBody()->GetWorldCenter(), 1);
		}
	}

	m_playerPrefab->Update(InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_X),
		InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y),
		InputManager::Get()->GetAxis(CONTROLLER_AXIS_LEFT_X));

	//DOUBLE JUMP
	if (m_doubleJump && InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A) != 0.0f && m_isMidAir) 
	{
		std::cout << "I JUMP TWICE HAHA" << std::endl;
		m_doubleJump = false;
		GetBox().getBody()->ApplyForce(b2Vec2(0, 100), GetBox().getBody()->GetWorldCenter(), 1);

	}

	GLfloat xPos = GetBox().getBody()->GetPosition().x;
	GLfloat yPos = GetBox().getBody()->GetPosition().y;
	GLfloat xScale = GetBox().getScale().x;
	GLfloat yScale = GetBox().getScale().y;

	m_playerPrefab->GetPlayerPrefab()->SetPosition(glm::vec3(xPos + 0.5, yPos + GetBox().getScale().y - 6, 0));

	m_playerSprite.update(glm::vec2(xPos - (GetBox().getScale().x / 2), yPos - (GetBox().getScale().y / 2)), glm::vec2(GetBox().getScale().x, GetBox().getScale().y));

	//////////////////////////////////////////////////////////


}

//::.. RENDER ..:://
void Player::Render(Camera camera) {

	Transform transform;
	//m_playerSprite.Bind();
	//m_playerSprite.Update(transform, camera);
	//m_playerSprite.draw();
//	glUseProgram(0);

	m_playerPrefab->Render(camera);

}
Box Player::GetBox()
{
	return m_boundingBox;
}

PlayerPrefab* Player::GetPrefab()
{
	return m_playerPrefab;
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

//void Player::StartContact() {
//	m_contact = true;
//}
//void Player::EndContact() {
//	m_contact = false;
//}