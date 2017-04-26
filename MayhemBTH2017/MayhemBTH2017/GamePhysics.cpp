#include "GamePhysics.h"





GamePhysics::GamePhysics()
{
}

GamePhysics::~GamePhysics()
{
}

void GamePhysics::enterWorld()
{

	//Get deltatime
	m_time = TimeManager::Get();
	b2Vec2 gravity(0.0f, -1.8f);

	m_world = std::make_unique<b2World>(gravity);

	m_collision.CreateBoundingBoxes(m_world.get());

	//Set spawn position of player AND SIZE OF SPRITE BOX

	//PLAYER
	m_player.Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0,2.0));

	///////////////////////////////////////////////////////////////////

	//Power up

	///////////////////////////////////////////////////////////////////


	//FIXTURES FOR COLLISIONS

	//player fixture is of type PLAYER
	m_player.SetCategoryBits(CATEGORY_PLAYER);
	m_player.SetMaskBits(CATEGORY_POWERUP);

}

void GamePhysics::Update()
{

	//Update player bounding box sprite position to the position of the player mesh

	if (!(m_player.GetCategoryBits() & powerUpFixture.filter.maskBits) != 0 && (powerUpFixture.filter.categoryBits & m_player.GetMaskBits()) != 0) {
		std::cout << "touching" << std::endl;
	}

	m_world->Step(1.0f / 60.0f, 6, 2);
	
	m_player.Update();
	

	m_world->Step(1.0f / 60.0f, 6, 2);

}

glm::vec3 GamePhysics::GetPosition() {

	return m_transform.GetPosition();

}

void GamePhysics::Render(Camera camera) {
	camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
	m_collision.DrawCollider(camera);

	m_player.Render(camera);
}