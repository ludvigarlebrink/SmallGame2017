#include "GamePhysics.h"





GamePhysics::GamePhysics()
{

}

GamePhysics::~GamePhysics()
{

}

void GamePhysics::EnterWorld()
{

	Contact contactlist;
	//Get deltatime
	m_time = TimeManager::Get();
	b2Vec2 gravity(0.0f, -9.8f);

	m_world = std::make_unique<b2World>(gravity);
//	m_world->SetContactListener(&contactlist);

	m_floorCollider.CreateBoundingBoxes(m_world.get());

	//Set spawn position of player AND SIZE OF SPRITE BOX

	//PLAYER
	m_player.Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0, 2.0));

	///////////////////////////////////////////////////////////////////

	//Weapon

	Prefab * gun = PrefabManager::Instantiate("Player");

	gun->SetScale(glm::vec3(1, 1, 1));

	gun->SetPosition(glm::vec3(30.0f, 30.0f, 0.0));

	Prefab * projectile = PrefabManager::Instantiate("Player");


	projectile->SetScale(glm::vec3(1, 1, 1));

	m_weapon = Weapon(gun);
	

	m_weapon.Bullet();

	///////////////////////////////////////////////////////////////////



	///

	//FIXTURES FOR COLLISIONS

	//player fixture is of type PLAYER
	m_player.SetCategoryBits(PLAYER);
	m_player.SetMaskBits(POWERUP);


}

void GamePhysics::Update()
{

	//Update player bounding box sprite position to the position of the player mesh

	if (!(m_player.GetCategoryBits() & powerUpFixture.filter.maskBits) != 0 && (powerUpFixture.filter.categoryBits & m_player.GetMaskBits()) != 0) {
		std::cout << "touching" << std::endl;
	}

	m_world->Step(1.0f / 10.0f, 6, 2);

	m_player.Update();

	m_weapon.Update(m_player.GetPrefab()->GetPosition() + glm::vec3(5, 5, 0));

	if (InputManager::Get()->GetButtonHeld(CONTROLLER_BUTTON_Y))
	{
		if (m_weapon.FireRate(0.1f))
		{
			m_weapon.FireGun(b2Vec2(InputManager::Get()->GetAxisDirection(CONTROLLER_AXIS_LEFTX) * 1000, 0 ),m_world.get());
		}
			
		
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

}