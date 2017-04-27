#include "GamePhysics.h"



GamePhysics::GamePhysics()
{
}


GamePhysics::~GamePhysics()
{
}


void GamePhysics::EnterWorld()
{

	//Get deltatime
	m_time = TimeManager::Get();
	b2Vec2 gravity(0.0f, -25.8f);

	m_world = std::make_unique<b2World>(gravity);

	m_floorCollider.CreateBoundingBoxes(m_world.get());

	//Set spawn position of player AND SIZE OF SPRITE BOX

	//PLAYER
	m_player.Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0, 2.0));

	///////////////////////////////////////////////////////////////////

	//Weapon

	Prefab * gun = PrefabManager::Instantiate("Player");

	gun->SetPosition(glm::vec3(30.0f, 30.0f, 0.0));

	Prefab * projectile = PrefabManager::Instantiate("Player");



	m_weapon = Weapon(gun, projectile);

	m_weapon.SetProjectileType(0.99f, 1.0f, 0.0f, 0.01f, 5.0f);

	///////////////////////////////////////////////////////////////////
	

	//FIXTURES FOR COLLISIONS

	//player fixture is of type PLAYER


	//gamefloor fixture



	for (int i = 0; i < m_floorCollider.GetBoxes().size(); i++) {
		std::cout << "mask " << m_player.GetBox().getFixture()->GetFilterData().maskBits << std::endl;
		std::cout << "category " << m_floorCollider.GetBoxes().at(i).getFixture()->GetFilterData().categoryBits << std::endl;
		
	}


}

void GamePhysics::Update()
{
	b2ContactFilter filter2; 

		//Update player bounding box sprite position to the position of the player mesh

		m_world->Step(1.0f / 60.0f, 6, 2);

		m_player.Update();

	

		m_weapon.Update(glm::vec3(m_player.GetPrefab()->GetPosition().x + 10, m_player.GetPrefab()->GetPosition().y, m_player.GetPrefab()->GetPosition().z));

		if (InputManager::Get()->GetButtonDown(CONTROLLER_BUTTON_A))
		{
			m_weapon.Shoot(b2Vec2(1000, 1000), 0.1f, m_world.get());
		}


		m_world->Step(1.0f / 60.0f, 6, 2);

}

glm::vec3 GamePhysics::GetPosition() {

	return m_transform.GetPosition();

}

void GamePhysics::Render(Camera camera) {
	camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
	m_floorCollider.DrawCollider(camera);

	m_player.Render(camera);

	m_weapon.Render(camera);

}