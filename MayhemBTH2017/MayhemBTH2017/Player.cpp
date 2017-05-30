#include "Player.h"



//::..CONSTRUCTORS..:://
Player::Player(b2World* world, glm::vec2 pos, glm::vec2 scale, int controllerID)
{
	m_contact = false;

	m_dead = false;

	m_hitByProjectile = -1;


	m_input = nullptr;
	m_playerPrefab = nullptr;
	m_healthBar = nullptr;
	m_healthBarBackground = nullptr;
	m_world = nullptr;
}

Player::Player()
{
	m_contact = false;

	m_dead = false;

	m_hitByProjectile = -1;


}


Player::~Player()
{
	Free();
}


//::..INITIALIZERS..:://
void Player::Init(b2World* world, glm::vec2 pos, glm::vec2 scale, int controllerID)
{
	m_input = nullptr;
	m_playerPrefab = nullptr;
	m_healthBar = nullptr;
	m_healthBarBackground = nullptr;
	m_world = nullptr;

	m_particleTexture1 = m_textureHandler.Import(".\\Assets\\Textures\\particle_glow.png");
	m_particleTexture2 = m_textureHandler.Import(".\\Assets\\Textures\\debree.png");
	m_particleTexture3 = m_textureHandler.Import(".\\Assets\\Textures\\fireball.png");
	m_particleTexture4 = m_textureHandler.Import(".\\Assets\\Textures\\spark2.png");
	m_particleTexture5 = m_textureHandler.Import(".\\Assets\\Textures\\blue_explosion.png");
	m_particleTexture6 = m_textureHandler.Import(".\\Assets\\Textures\\ring.png");
	m_particleTexture7 = m_textureHandler.Import(".\\Assets\\Textures\\spark2.png");

	//MARTIN TEST SHIT REMOVE
	//m_testCon = new PlayerController;
	//TEST END
	m_input = InputManager::Get();
	m_soundManager = SoundManager::Get();

	//Initiate the players bounding box
	m_contact = false;
	//Load player MESH

	m_world = world;

	SetControllerID(controllerID);

	m_playerPrefab = new PlayerPrefab(m_controllerID);

	//SET BOUNDING BOX SIZE 
	m_boundingBox.InitDynamic(world, pos, glm::vec2(m_playerPrefab->GetPlayerPrefab()->GetScale().x + 1, m_playerPrefab->GetPlayerPrefab()->GetScale().y * 3.0f));
	//sprite for size of bouding box
	m_playerSprite.Init(".\\Assets\\GLSL\\ColliderShader", 0, 0);
	//Load player shader
	//m_shader.Init(".\\Assets\\GLSL\\ToonShader", 0, 0);

	//GetBox().getFixture()->SetDensity(0.1);
	GetBox().getFixture()->SetFriction(10.0);
	GetBox().getFixture()->SetRestitution(0.0);
	GetBox().getBody()->SetLinearDamping(0.0);
	GetBox().getBody()->ResetMassData();

	b2Filter filter;
	if (m_controllerID == 0)
	{
		filter.categoryBits = PLAYER1;
		filter.maskBits = BOUNDARY | POWERUP | PROJECTILE2 | PROJECTILE3 | PROJECTILE4;
	}
	if (m_controllerID == 1)
	{
		filter.categoryBits = PLAYER2;
		filter.maskBits = BOUNDARY | POWERUP | PROJECTILE1 | PROJECTILE3 | PROJECTILE4;
	}

	if (m_controllerID == 2)
	{
		filter.categoryBits = PLAYER3;
		filter.maskBits = BOUNDARY | POWERUP | PROJECTILE1 | PROJECTILE2 | PROJECTILE4;
	}
	if (m_controllerID == 3)
	{
		filter.categoryBits = PLAYER4;
		filter.maskBits = BOUNDARY | POWERUP | PROJECTILE1 | PROJECTILE2 | PROJECTILE3;
	}
	GetBox().getFixture()->SetFilterData(filter);

	GetBox().getBody()->SetUserData(this);

	m_collidedPowerUp = false;

	//set weapon

	Prefab * gun = PrefabManager::Instantiate("lukas", nullptr, nullptr, 0, "Candle");

	m_healthBar = PrefabManager::Instantiate("lukas", nullptr, nullptr, 0, "Candle");
	m_healthBarBackground = PrefabManager::Instantiate("lukas", nullptr, nullptr, 0, "Candle");

	m_healthBar->Create();
	m_healthBarBackground->Create();

	gun->SetScale(glm::vec3(2, 2, 2));

	gun->SetPosition(glm::vec3(30.0f, 30.0f, 0.0));

	Prefab * projectile = PrefabManager::Instantiate("bullet", nullptr, nullptr, 0, "Candle");
	Prefab * projectile2 = PrefabManager::Instantiate("sword3", nullptr, nullptr, 0, "Candle");
	Prefab * projectile3 = PrefabManager::Instantiate("spike2", nullptr, nullptr, 0, "Candle");
	Prefab * projectile4 = PrefabManager::Instantiate("Rifle", nullptr, nullptr, 0, "Candle");
	Prefab * projectile5 = PrefabManager::Instantiate("missile3", nullptr, nullptr, 0, "Candle");
	Prefab * projectile6 = PrefabManager::Instantiate("boomerang", nullptr, nullptr, 0, "Candle");
	Prefab * projectile7 = PrefabManager::Instantiate("spear", nullptr, nullptr, 0, "Candle");

	projectile->SetScale(glm::vec3(1, 1, 1));

	//	m_weapon = Weapon(gun, projectile);
	m_weapons[0] = new Weapon(gun, projectile, m_controllerID);
	m_weapons[0]->SetProjectileType(0.6, 1.0, 0.5f, 0.2f, 0.15f, 10, m_controllerID, 0.0);
	m_weapons[0]->SetWeaponSound("assault_rifle");
	m_weapons[0]->SetFirePower(150.0);
	m_weapons[0]->SetDamage(0.1f);


	m_weapons[1] = new Weapon(gun, projectile2, m_controllerID);
	m_weapons[1]->SetProjectileType(0.1f, 1.0f, 0.0f, 0.0f, 3.0f, 10, m_controllerID, 0.0);
	m_weapons[1]->SetWeaponSound("scifi_weapon");
	m_weapons[1]->SetFirePower(20.0f);
	m_weapons[1]->SetDamage(1.0f);

	m_weapons[2] = new Weapon(gun, projectile3, m_controllerID);
	m_weapons[2]->SetProjectileType(0.9f, 1.0f, 0.0f, 0.0f, 0.5f, 15, m_controllerID, 5.0);
	m_weapons[2]->SetWeaponSound("shuriken");
	m_weapons[2]->SetFirePower(100.0f);
	m_weapons[2]->SetDamage(0.3f);


	m_weapons[3] = new Weapon(gun, projectile4, m_controllerID);
	m_weapons[3]->SetProjectileType(0.2f, 1.0f, 0.0f, 0.0f, 0.5f, 18, m_controllerID, 0.0);
	m_weapons[3]->SetWeaponSound("heavy_shot");
	m_weapons[3]->SetFirePower(100.0f);
	m_weapons[3]->SetDamage(0.3f);

	m_weapons[4] = new Weapon(gun, projectile5, m_controllerID);
	m_weapons[4]->SetProjectileType(0.1f, 1.0f, 0.0f, 0.0f, 0.5f, 12, m_controllerID, 0.0);
	m_weapons[4]->SetWeaponSound("massive_shot");
	m_weapons[4]->SetFirePower(100.0f);
	m_weapons[4]->SetDamage(0.3f);

	m_weapons[5] = new Weapon(gun, projectile6, m_controllerID);
	m_weapons[5]->SetProjectileType(0.8f, 1.0f, 0.0f, 0.0f, 0.5f, 11, m_controllerID, 0.0);
	m_weapons[5]->SetWeaponSound("scifi2");
	m_weapons[5]->SetFirePower(100.0f);
	m_weapons[5]->SetDamage(0.3f);

	m_weapons[6] = new Weapon(gun, projectile7, m_controllerID);
	m_weapons[6]->SetProjectileType(0.7f, 1.0f, 0.0f, 0.0f, 0.5f, 14, m_controllerID, 0.0);
	m_weapons[6]->SetWeaponSound("default_gun");
	m_weapons[6]->SetFirePower(100.0f);
	m_weapons[6]->SetDamage(0.3f);

	m_currentWeapon = 0;

	m_life = 1.0f;

	m_healthBarBackground->SetScale(glm::vec3(1, 0.6, m_life * 5));
	m_healthBarBackground->Rotate(glm::vec3(0.0, 90.0, 0.0));
	m_healthBarBackground->SetPosition(glm::vec3(m_boundingBox.getBody()->GetPosition().x + 3, m_boundingBox.getBody()->GetPosition().y + 5, 0.0));

	m_healthBar->SetScale(glm::vec3(1, 0.6, m_life * 5));
	m_healthBar->Rotate(glm::vec3(0.0, 90.0, 0.0));
	m_healthBar->SetPosition(glm::vec3(m_boundingBox.getBody()->GetPosition().x + 3, m_boundingBox.getBody()->GetPosition().y + 5, 0.0));
	//Set fixture 

}

void Player::Free()
{

	for (size_t i = 0; i < 7; i++)
	{
		delete m_weapons[i];
	}

	if (m_playerPrefab != nullptr)
	{
		delete m_playerPrefab;
		m_playerPrefab = nullptr;
	}

	if (m_healthBar != nullptr)
	{
		delete m_healthBar;
		m_healthBar = nullptr;
	}

	if (m_healthBarBackground != nullptr) {
		delete m_healthBarBackground;
		m_healthBarBackground = nullptr;
	}

	delete m_particleTexture1;
	delete m_particleTexture2;
	delete m_particleTexture3;
	delete m_particleTexture4;
	delete m_particleTexture5;
	delete m_particleTexture6;
	delete m_particleTexture7;

	// LUKAS DELETE WORLD
}

void Player::Update(Player * p_arr) {
	//std::cout << m_currentWeapon << std::endl;
	if (m_boundingBox.getBody()->GetPosition().y < -5.0f)
	{
		m_dead = true;
	}

	if (m_currentWeapon > 6)
	{
		m_currentWeapon = 0;
	}

	m_healthBar->SetPosition(glm::vec3(m_boundingBox.getBody()->GetPosition().x + 3, m_boundingBox.getBody()->GetPosition().y + 5, 0.0));
	m_healthBar->SetPosition(glm::vec3(m_healthBar->GetPosition().x - m_life * 2.5f, m_healthBar->GetPosition().y, m_healthBar->GetPosition().z));

	m_healthBarBackground->SetPosition(glm::vec3(m_boundingBox.getBody()->GetPosition().x+0.5f , m_boundingBox.getBody()->GetPosition().y + 5, 0.0));

	if (m_input->GetAxisRaw(CONTROLLER_AXIS_TRIGGERRIGHT, m_controllerID) > 0.0001f)
	{
		if (m_weapons[m_currentWeapon]->FireRate(m_weapons[m_currentWeapon]->GetFireRate()))
		{
			m_weapons[m_currentWeapon]->Shoot(m_world, glm::vec3(GetPrefab()->GetProjectileSpawnPoint().x, GetPrefab()->GetProjectileSpawnPoint().y, GetPrefab()->GetProjectileSpawnPoint().z), m_controllerID);


			if (m_currentWeapon == 0) {

			}

			if (m_currentWeapon == 1) {
				m_weapons[m_currentWeapon]->InitParticleSystem(".\\Assets\\GLSL\\Particle2", glm::vec4(1.0, 0.0, 0.0, 1.0), 0.0, 10, 0.0f);
				m_weapons[m_currentWeapon]->SetParticleTexture(m_particleTexture2);
			}

			if (m_currentWeapon == 2) {
				m_weapons[m_currentWeapon]->InitParticleSystem(".\\Assets\\GLSL\\Particle2", glm::vec4(0.0, 0.0, 1.0, 1.0), 0.0, 10, 0.0f);
				m_weapons[m_currentWeapon]->SetParticleTexture(m_particleTexture3);
			}

			if (m_currentWeapon == 3) {
				m_weapons[m_currentWeapon]->InitParticleSystem(".\\Assets\\GLSL\\Particle4", glm::vec4(1.0, 1.0, 0.0, 1.0), 0.0, 10, 0.0f);
				m_weapons[m_currentWeapon]->SetParticleTexture(m_particleTexture4);
			}

			if (m_currentWeapon == 4) {
				m_weapons[m_currentWeapon]->InitParticleSystem(".\\Assets\\GLSL\\Particle5", glm::vec4(0.0, 1.0, 1.0, 1.0), 0.0, 10, 0.0f);
				m_weapons[m_currentWeapon]->SetParticleTexture(m_particleTexture5);

			}
			if (m_currentWeapon == 5) {
				m_weapons[m_currentWeapon]->InitParticleSystem(".\\Assets\\GLSL\\Particle6", glm::vec4(1.0, 0.0, 1.0, 1.0), 0.0, 10, 0.0f);
				m_weapons[m_currentWeapon]->SetParticleTexture(m_particleTexture6);
			}

			if (m_currentWeapon == 6) {
				m_weapons[m_currentWeapon]->InitParticleSystem(".\\Assets\\GLSL\\Particle1", glm::vec4(1.0, 0.0, 1.0, 1.0), 0.0, 10, 0.0f);
				m_weapons[m_currentWeapon]->SetParticleTexture(m_particleTexture7);
			}

		}
	}


	if (m_contact)
	{
		if (m_collidedProjectile)
		{
			int hitSound = rand() % 4;

			if (hitSound == 0 && m_life > 0.0f) {
				m_soundManager->PlaySFX("player_hit1");
				m_soundManager->PlaySFX("man_scream1");
			}
			if (hitSound == 1 && m_life > 0.0f) {
				m_soundManager->PlaySFX("player_hit2");
				m_soundManager->PlaySFX("man_scream2");
			}
			if (hitSound == 2 && m_life > 0.0f) {
				m_soundManager->PlaySFX("player_hit3");
				m_soundManager->PlaySFX("man_scream3");
			}

			if (hitSound == 3 && m_life > 0.0f) {
				m_soundManager->PlaySFX("player_hit3");
				m_soundManager->PlaySFX("man_scream4");
			}


			ScoreManager::AddHitScore(m_hitByProjectileID);



			m_life -= p_arr[m_hitByProjectileID].GetDamage();


			m_healthBar->SetPosition(glm::vec3(m_boundingBox.getBody()->GetPosition().x + 3, m_boundingBox.getBody()->GetPosition().y + 5, 0.0));
			m_healthBar->SetPosition(glm::vec3(m_healthBar->GetPosition().x - m_life * 2.5f, m_healthBar->GetPosition().y, m_healthBar->GetPosition().z));
			m_healthBar->SetScale(glm::vec3(1, 0.6, m_life * 5));

			//m_healthBarBackground->SetPosition(glm::vec3(m_boundingBox.getBody()->GetPosition().x, m_boundingBox.getBody()->GetPosition().y + 5, 0.0));


			if (m_life <= 0.0f)
			{
				int hitSound = rand() % 3;

				if (hitSound == 0) {
					m_soundManager->PlaySFX("player_hit1");
					m_soundManager->PlaySFX("death_1");
				}
				if (hitSound == 1) {
					m_soundManager->PlaySFX("player_hit2");
					m_soundManager->PlaySFX("death_2");
				}
				if (hitSound == 2) {
					m_soundManager->PlaySFX("player_hit3");
					m_soundManager->PlaySFX("death_3");
				}


				ScoreManager::AddKill(m_hitByProjectileID);
				m_healthBar->SetScale(glm::vec3(1.0, 0.7, 0));
				ScoreManager::AddDeath(m_controllerID);
				m_dead = true;
			}
		}
		if (m_collidedPowerUp)
		{
			int atomic = rand() % 6;
			if (atomic != 5) {
				m_currentWeapon = rand() % 6 + 1;
			}
			if (atomic == 5) {
				m_soundManager->PlaySFX("siren");
				m_soundManager->PlayAmbient("airplane");
				AtomicBomb::StartBombSequence();
			}
			m_collidedPowerUp = false;
		}
		m_contact = false;
	}

	if (m_dead)
	{
		int spawn = rand() % 80;
		m_time += TimeManager::Get()->GetDeltaTime();
		Respawn(glm::vec2(spawn, 70));

		m_currentWeapon = 0;

		if (Timer(2))
		{
			Respawn(glm::vec2(spawn, 30));
			m_boundingBox.getBody()->ApplyForce(b2Vec2(1.0, 1.0), m_boundingBox.getBody()->GetWorldCenter(), true);
			m_life = 1.0;
			m_healthBar->SetScale(glm::vec3(1, 0.6, m_life * 5));
			m_dead = false;
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
	GLfloat leftVelocity = GetBox().getBody()->GetLinearVelocity().x * InputManager::Get()->GetAxis(CONTROLLER_AXIS_LEFT_X);


	// THIS STUFF WORKS

	if (m_input->GetAxisRaw(CONTROLLER_AXIS_LEFT_X, m_controllerID))
	{

		if (m_isMidAir) {

			GetBox().getBody()->ApplyForce(b2Vec2(m_input->GetAxis(CONTROLLER_AXIS_LEFT_X, m_controllerID)*(-150)*TimeManager::Get()->GetDeltaTime(), 0), GetBox().getBody()->GetWorldCenter(), 1);

		}
		if (!m_isMidAir) {

			GetBox().getBody()->SetLinearVelocity(b2Vec2(m_input->GetAxis(CONTROLLER_AXIS_LEFT_X, m_controllerID)*(-200)*TimeManager::Get()->GetDeltaTime(), 0));
		}


	}
	// ** //



	m_playerPrefab->Update(InputManager::Get()->GetAxis(CONTROLLER_AXIS_RIGHT_X, m_controllerID),
		m_input->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y, m_controllerID),
		m_input->GetAxisRaw(CONTROLLER_AXIS_LEFT_X, m_controllerID));


	if (m_input->GetButtonDown(CONTROLLER_BUTTON_LEFTBUTTON, m_controllerID) != 0.0f)
	{


		if (!m_isMidAir) {

			//First jump
			GetBox().getBody()->ApplyForce(b2Vec2(0, 130), GetBox().getBody()->GetWorldCenter(), 1);
			m_doubleJump = true;


			//m_player.GetBox().getBody()->ApplyLinearImpulse(b2Vec2(0, impulse), m_player.GetBox().getBody()->GetWorldCenter(), 1);
		}
	}

	//DOUBLE JUMP
	if (m_doubleJump && m_input->GetButtonDown(CONTROLLER_BUTTON_LEFTBUTTON, m_controllerID) != 0.0f && m_isMidAir)
	{
		m_doubleJump = false;
		GetBox().getBody()->ApplyForce(b2Vec2(0, 130), GetBox().getBody()->GetWorldCenter(), 1);

	}

	GLfloat xPos = GetBox().getBody()->GetPosition().x;
	GLfloat yPos = GetBox().getBody()->GetPosition().y;
	GLfloat xScale = GetBox().getScale().x;
	GLfloat yScale = GetBox().getScale().y;

	m_playerPrefab->GetPlayerPrefab()->SetPosition(glm::vec3(xPos + 0.5, yPos + GetBox().getScale().y - 6, 0));

	//////////////////////////////////////////////////////////
	for (int i = 0; i < 7; i++)
	{
		m_weapons[i]->Update(GetPrefab()->GetProjectileSpawnPoint(), b2Vec2(1.0, 1.0));
	}
}


void Player::Respawn(glm::vec2 pos)
{
	m_boundingBox.getBody()->SetTransform(b2Vec2(pos.x, pos.y), 0.0f);
}


Box Player::GetBox()
{
	return m_boundingBox;
}

float Player::GetDamage()
{
	return m_weapons[m_currentWeapon]->GetDamage();
}


PlayerPrefab* Player::GetPrefab()
{
	return m_playerPrefab;
}

int Player::GetProjectileID()
{
	return m_hitByProjectileID;
}


void Player::StartContact(bool projectile, bool powerup)
{
	m_contact = true;

	if (projectile)
	{
		m_collidedProjectile = true;
		m_collidedPowerUp = false;
	}
	if (powerup)
	{
		m_collidedPowerUp = true;
		m_collidedProjectile = false;
	}

}


void Player::EndContact()
{
}


int Player::GetControllerID()
{
	return m_controllerID;
}


void Player::UpdateParticles()
{

	m_weapons[m_currentWeapon]->UpdateParticles();
}


Prefab * Player::GetHealthBar()
{
	return m_healthBar;
}


Prefab * Player::GetHealthBarBackground()
{
	return m_healthBarBackground;
}





//::.. SET FUNCTIONS ..:://
void Player::SetCategoryBits(short CATEGORY)
{
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


void Player::SetControllerID(int ID)
{
	m_controllerID = ID;
}


void Player::Hit(int projectileID)
{
	m_hitByProjectileID = projectileID;
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

//::.. RENDER ..:://
void Player::Render(Camera camera) {

	//Renders the player and the gun 
	m_playerPrefab->Render(camera);

	//Renders projectiles of a weapon and its particles
	for (int i = 0; i < 7; i++)
	{
		m_weapons[i]->Render(camera);
	}
}


void Player::RenderShadow(Camera camera)
{

	//Renders the player and the gun 
	m_playerPrefab->RenderShadow(camera);

	//Renders projectiles of a weapon and its particles
	for (int i = 0; i < 7; i++)
	{
		m_weapons[i]->RenderShadow(camera);

	}
}