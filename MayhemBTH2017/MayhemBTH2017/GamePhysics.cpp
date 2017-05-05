#include "GamePhysics.h"





GamePhysics::GamePhysics()
{
	m_loadWorld = false;
}

GamePhysics::~GamePhysics()
{

}

void GamePhysics::EnterWorld()
{

	//Get deltatime
	m_time = TimeManager::Get();
	b2Vec2 gravity(0.0f, -9.81f);

	m_world = std::make_unique<b2World>(gravity);

	m_floorCollider.CreateBoundingBoxes(m_world.get());

	//at global scope

	//in FooTest constructor
	m_world.get()->SetContactListener(new MyContactListener());

	//Set spawn position of player AND SIZE OF SPRITE BOX


	//Weapon

	Prefab * gun = PrefabManager::Instantiate("Player");

	gun->SetScale(glm::vec3(2, 2, 2));

	gun->SetPosition(glm::vec3(30.0f, 30.0f, 0.0));

	Prefab * projectile = PrefabManager::Instantiate("Candle", nullptr, nullptr, 0, "Candle");

	projectile->SetScale(glm::vec3(1, 1, 1));


	///////////////////////////////////////////////////////////////////
	glm::vec2 spawnPos[2];
	spawnPos[0] = glm::vec2(42, 24);
	spawnPos[1] = glm::vec2(15, 24);



	//PLAYER
	m_player[0].Init(m_world.get(), spawnPos[0], glm::vec2(2.0, 2.0));
	m_player[1].Init(m_world.get(), spawnPos[1], glm::vec2(2.0, 2.0));

	//Player Weapons
	m_weapon[0] = Weapon(gun, projectile);
	m_weapon[1] = Weapon(gun, projectile);


	m_weapon[0].InitParticleSystem(".\\Assets\\GLSL\\GeometryPass", glm::vec4(1.0, 0.0, 0.0, 1.0), 1.0f, 500);
	m_weapon[0].SetProjectileType(0.8f, 1.0f, 0.0f, 0.1f, 5.0f, 10);

	m_weapon[1].InitParticleSystem(".\\Assets\\GLSL\\GeometryPass", glm::vec4(1.0, 0.0, 0.0, 1.0), 1.0f, 500);
	m_weapon[1].SetProjectileType(0.8f, 1.0f, 0.0f, 0.1f, 5.0f, 10);

	///////////////////////////////////////////////////////////////////


	//FIXTURES FOR COLLISIONS


	//player fixture is of type PLAYER
	m_player[0].SetCategoryBits(PLAYER);
	m_player[0].SetMaskBits(POWERUP);
	//player fixture is of type PLAYER
	m_player[1].SetCategoryBits(PLAYER);
	m_player[1].SetMaskBits(POWERUP);

	m_loadWorld = true;
}

void GamePhysics::Update()
{
	switch (m_loadWorld) {
	case true:
	{


		m_world->Step(1.0f / 30.0f, 6, 2);

		for (b2Contact* contact = m_world->GetContactList(); contact; contact = contact->GetNext())
		{
			if (contact->IsTouching())
			{
				Projectile* proj = static_cast<Projectile*>(contact->GetFixtureB()->GetBody()->GetUserData());
				if (proj != NULL)
				{
					//std::cout << " den nuddar något som kanske nuddar något osv .." << std::endl;
				}
			}

		}


		//Update players and their weapons
		for (int i = 0; i < 2; i++) {
			m_player[i].Update();
						m_weapon[i].Update(m_player[i].GetPrefab()->GetProjectileSpawnPoint(), b2Vec2(1.0, 1.0));

			if (InputManager::Get()->GetAxis(CONTROLLER_AXIS_TRIGGERRIGHT) != 0)
			{
				if (m_weapon[i].FireRate(0.2f))
				{

					m_weapon[i].Shoot(10.0f, m_world.get(), glm::vec3(m_player[i].GetPrefab()->GetProjectileSpawnPoint().x, m_player[i].GetPrefab()->GetProjectileSpawnPoint().y, m_player[i].GetPrefab()->GetProjectileSpawnPoint().z));
				}
			}
		}


		m_world->Step(1.0f / 30.0f, 6, 2); }
	break;
	case false:
		std::cout << "LOADING" << std::endl;
		EnterWorld();
		break;
		//Update player bounding box sprite position to the position of the player mesh
	}
}

glm::vec3 GamePhysics::GetPosition() {

	return m_transform.GetPosition();

}

void GamePhysics::Render(Camera camera) {
	camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));


	m_floorCollider.DrawCollider(camera);
	for (int i = 0; i < 2; i++) {
		m_player[i].Render(camera);
		m_weapon[i].Render(camera);
		m_weapon[i].RenderParticles(camera);
	}


}