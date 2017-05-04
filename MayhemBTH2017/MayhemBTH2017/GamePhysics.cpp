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
	b2Vec2 gravity(0.0f, -1.21f);

	m_world = std::make_unique<b2World>(gravity);

	m_floorCollider.CreateBoundingBoxes(m_world.get());

	//at global scope

	//in FooTest constructor
	m_world.get()->SetContactListener(new MyContactListener());

	//Set spawn position of player AND SIZE OF SPRITE BOX

	//PLAYER
	m_player.Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0, 2.0));

	///////////////////////////////////////////////////////////////////

	//Weapon

	Prefab * gun = PrefabManager::Instantiate("Player");

	gun->SetScale(glm::vec3(2, 2, 2));

	gun->SetPosition(glm::vec3(30.0f, 30.0f, 0.0));

	Prefab * projectile = PrefabManager::Instantiate("Player");

	projectile->SetScale(glm::vec3(1, 1, 1));

	//	m_weapon = Weapon(gun, projectile);
	m_weapon = Weapon(gun, projectile);


	m_weapon.InitParticleSystem(".\\Assets\\GLSL\\GeometryPass", glm::vec4(1.0, 0.0, 0.0, 1.0), 2.0f, 500);
	m_weapon.SetProjectileType(0.3f, 1.0f, 0.0f, 0.1f, 5.0f, 10);


	///////////////////////////////////////////////////////////////////


	//FIXTURES FOR COLLISIONS


	//player fixture is of type PLAYER
	m_player.SetCategoryBits(PLAYER);
	m_player.SetMaskBits(POWERUP);
	m_loadWorld = true;
}

void GamePhysics::Update()
{
	switch (m_loadWorld) {
	case true:
	{
		if (!(m_player.GetCategoryBits() & powerUpFixture.filter.maskBits) != 0 && (powerUpFixture.filter.categoryBits & m_player.GetMaskBits()) != 0) {

		}

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

		m_player.Update();
		m_weapon.Update(m_player.GetPrefab()->GetProjectileSpawnPoint(), b2Vec2(1.0, 1.0));

		if (InputManager::Get()->GetButtonHeld(CONTROLLER_BUTTON_Y))
		{
			if (m_weapon.FireRate(0.2f))
			{
				m_weapon.Shoot(b2Vec2(450, 450), m_world.get(), glm::vec3(m_player.GetPrefab()->GetProjectileSpawnPoint().x, m_player.GetPrefab()->GetProjectileSpawnPoint().y, m_player.GetPrefab()->GetProjectileSpawnPoint().z));
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

	m_player.Render(camera);

	m_weapon.Render(camera);
	m_weapon.RenderParticles(camera);

}