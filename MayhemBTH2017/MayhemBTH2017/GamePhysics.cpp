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
	b2Vec2 gravity(0.0f, -8.21f);

	m_world = std::make_unique<b2World>(gravity);

	m_floorCollider.CreateBoundingBoxes(m_world.get());

	//at global scope

	//in FooTest constructor
	m_world.get()->SetContactListener(new MyContactListener());

	//Set spawn position of player AND SIZE OF SPRITE BOX

	m_PH.Init(m_world.get(), 20);
	//PLAYER


	m_player[0].Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0, 2.0));
	m_player[0].SetCategoryBits(PLAYER);
	m_player[0].SetMaskBits(POWERUP);
	m_player[0].SetControllerID(0);

	m_player[1].Init(m_world.get(), glm::vec2(15, 24), glm::vec2(2.0, 2.0));
	m_player[1].SetCategoryBits(PLAYER);
	m_player[1].SetMaskBits(POWERUP);
	m_player[1].SetControllerID(1);

	///////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////

	//FIXTURES FOR COLLISIONS


	//player fixture is of type PLAYER
	m_loadWorld = true;
}

void GamePhysics::Update()
{
	m_particles.UpdateParticles();
	
	switch (m_loadWorld) {
	case true:
	{
		m_world->Step(1.0f / 20.0f, 8, 4);

		for (int i = 0; i < 2; i++) {

			m_player[i].Update();
			m_player[i].UpdateParticles();
		}

		m_PH.Update();

		m_world->Step(1.0f / 20.0f, 8, 4); 
	}
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

void GamePhysics::SetNrOfPlayers(int nrOf)
{
	m_nrOfPlayers = nrOf;
}

void GamePhysics::Render(Camera camera) {

	//camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
	m_floorCollider.DrawCollider(camera);

	for (int i = 0; i < 2; i++) {

		m_player[i].Render(camera);
	
	}

	m_PH.Render(camera);
}