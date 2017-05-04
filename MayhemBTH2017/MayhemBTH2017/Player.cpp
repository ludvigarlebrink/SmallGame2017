#include "Player.h"

//::..CONSTRUCTORS..:://
Player::Player(b2World* world, glm::vec2 pos, glm::vec2 scale) {

	Init(world, pos, scale);
	m_contact = false;

	m_killed = false;
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
	m_playerSprite.Init(".\\Assets\\GLSL\\ColliderShader", 0, 0);
	//Load player shader
	//m_shader.Init(".\\Assets\\GLSL\\ToonShader", 0, 0);

	GetBox().getFixture()->SetDensity(0.1);
	GetBox().getFixture()->SetFriction(1.0);
	GetBox().getFixture()->SetRestitution(0.0);
	GetBox().getBody()->SetLinearDamping(0.0);
	
	b2Filter filter;
	filter.categoryBits = PLAYER;
	filter.maskBits = BOUNDARY| PROJECTILE;
	GetBox().getFixture()->SetFilterData(filter);

	GetBox().getBody()->SetUserData(this);

	//Set fixture 

}

void Player::Update() {

	if (m_contact)
	{
		if (m_collidedProjectile)
		{
			m_killed = true;
		}		
	}
	else if(m_killed)
	{
		m_time += TimeManager::Get()->GetDeltaTime();
		Respawn(glm::vec2(70, 70));
		if (Timer(2))
		{
			Respawn(glm::vec2(40, 30));
			m_boundingBox.getBody()->ApplyForce(b2Vec2(1.0, 1.0), m_boundingBox.getBody()->GetWorldCenter(), true);
			m_killed = false;
		}
	}




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
			GetBox().getBody()->ApplyForce(b2Vec2(0, 150), GetBox().getBody()->GetWorldCenter(), 1);
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
		m_doubleJump = false;
		GetBox().getBody()->ApplyForce(b2Vec2(0, 170), GetBox().getBody()->GetWorldCenter(), 1);

	}

	GLfloat xPos = GetBox().getBody()->GetPosition().x;
	GLfloat yPos = GetBox().getBody()->GetPosition().y;
	GLfloat xScale = GetBox().getScale().x;
	GLfloat yScale = GetBox().getScale().y;

	m_playerPrefab->GetPlayerPrefab()->SetPosition(glm::vec3(xPos + 0.5, yPos + GetBox().getScale().y - 6, 0));

	//////////////////////////////////////////////////////////


}

void Player::Respawn(glm::vec2 pos)
{
	m_boundingBox.getBody()->SetTransform(b2Vec2(pos.x, pos.y), 0);
}

//::.. RENDER ..:://
void Player::Render(Camera camera) {

	Transform transform;
	//m_playerSprite.Bind();
	//m_playerSprite.Update(transform, camera);
	//m_playerSprite.draw();
	//glUseProgram(0);

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

void Player::StartContact(bool projectile)
{
	m_contact = true;

	if (projectile)
	{
		m_collidedProjectile = true;
	}
	
}

void Player::EndContact()
{
	m_contact = false;
}



//::.. SET FUNCTIONS ..:://
void Player::SetCategoryBits(short CATEGORY) {

	m_fixture.filter.categoryBits = CATEGORY;
}
void Player::SetMaskBits(short MASK) {

	m_fixture.filter.maskBits = MASK;

}

bool Player::Timer(float rate)
{
	if (m_time >= rate)
	{
		m_time = 0;
		return true;
	}
	return false;
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