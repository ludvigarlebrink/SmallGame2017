#include "GamePhysics.h"


MyContactListener * GamePhysics::m_contactListener = nullptr;



GamePhysics::GamePhysics()
	:m_world(b2Vec2(0.0f, -8.21f))
{	
	if (m_contactListener == nullptr)
	{
		m_contactListener = new MyContactListener;
	}

	m_loadWorld = false;
	m_shadowShader.Init("ShadowShader");
	m_shadowShader2.Init("ShadowShaderPlayer");
	m_shadowMap.Init();

	m_player[0].Init(&m_world, glm::vec2(42, 24), glm::vec2(2.0, 5.0), 0);
	m_player[1].Init(&m_world, glm::vec2(15, 24), glm::vec2(2.0, 5.0), 1);
}

GamePhysics::~GamePhysics()
{
	Free();
}

void GamePhysics::EnterWorld(Level & level)
{
	m_time = TimeManager::Get();

	if (m_powerupHandler.GetSpawn() == true)
	{
		m_powerupHandler.Free();
	}
	m_floorCollider.CreateBoundingBoxes(&m_world, level.GetName());

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
	m_world.Step(1.0f / 20.0f, 8, 5);

	for (int i = 0; i < 2; i++) 
	{

		m_player[i].Update();
	}

	m_powerupHandler.Update();

	m_world.Step(1.0f / 20.0f, 8, 5);
	//Update player bounding box sprite position to the position of the player mesh
}



glm::vec3 GamePhysics::GetPosition() {

	return m_transform.GetPosition();

}


void GamePhysics::SetNrOfPlayers(int nrOf)
{
	m_nrOfPlayers = nrOf;
}


void GamePhysics::Free()
{
}


void GamePhysics::Render(Camera camera) {


	m_transf.SetPosition(42.0, 24.0, -0.0);
	//m_shadowMap.FirstPass();
	//m_shadowShader.UpdateShadows(camera, m_transf);
	//m_floorCollider.DrawColliderShadowPass(camera);
	//m_shadowShader2.UpdateShadows(camera, m_transf);
	//
	//for (int i = 0; i < 1; i++) {
	//
	//	m_player[i].RenderShadow(camera);
	//}
	//
	//
	//m_shadowMap.SecPass();
	//m_shadowMap.Bind();
   
	m_floorCollider.DrawCollider(camera);
	for (int i = 0; i < 2; i++) {

		m_player[i].Render(camera);
	}
	
	m_powerupHandler.Render(camera);


	//glClear(GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 2; i++) {

		m_player[i].GetHealthBar()->Render(camera);
	}
}