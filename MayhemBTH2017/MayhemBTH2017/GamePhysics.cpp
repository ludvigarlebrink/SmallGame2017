#include "GamePhysics.h"


MyContactListener * GamePhysics::m_contactListener = nullptr;



GamePhysics::GamePhysics()
	:m_world(b2Vec2(0.0f, -3.50f))
{	
	if (m_contactListener == nullptr)
	{
		m_contactListener = new MyContactListener;
	}

	m_loadWorld = false;
	m_player[0].Init(&m_world, glm::vec2(42, 24), glm::vec2(2.0, 5.0), 0);
	m_player[1].Init(&m_world, glm::vec2(15, 24), glm::vec2(2.0, 5.0), 1);
}

GamePhysics::~GamePhysics()
{
	Free();
	delete m_texture;
}

void GamePhysics::EnterWorld(std::string levelName)
{
	m_texture = m_textureHandler.Import(".\\Assets\\Textures\\health.jpg");
	m_time = TimeManager::Get();

	m_floorCollider.CreateBoundingBoxes(&m_world, levelName);

	//at global scope

	//in FooTest constructor
	m_world.SetContactListener(m_contactListener);

	//Set spawn position of player AND SIZE OF SPRITE BOX
	m_powerupHandler.Init(&m_world);

	//player fixture is of type PLAYER
	m_loadWorld = true;
}


void GamePhysics::Update()
{
	m_world.Step(1.0f / 30.0f, 6, 2);

	for (int i = 0; i < 2; i++) 
	{

		m_player[i].Update();
	}

	m_powerupHandler.Update();

	m_world.Step(1.0f / 20.0f, 8, 5);
	//Update player bounding box sprite position to the position of the player mesh
}


glm::vec3 GamePhysics::GetPosition() 
{
	return m_transform.GetPosition();
}


void GamePhysics::SetNrOfPlayers(int nrOf)
{
	m_nrOfPlayers = nrOf;
}


void GamePhysics::Free()
{

}


void GamePhysics::Render(Camera camera) 
{
	m_transf.SetPosition(42.0, 24.0, -0.0);
	m_floorCollider.DrawCollider(camera);
	for (int i = 0; i < 2; i++) {

		m_player[i].Render(camera);
	}
	
	m_powerupHandler.Render(camera);

	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < 2; i++) 
	{

		m_player[i].GetHealthBar()->SetAlbedoID(m_texture->GetTexture());
		m_player[i].GetHealthBar()->Render(camera);
	}
	glEnable(GL_DEPTH_TEST);
}