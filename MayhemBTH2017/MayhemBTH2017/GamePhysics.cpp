#include "GamePhysics.h"


MyContactListener * GamePhysics::m_contactListener = nullptr;



GamePhysics::GamePhysics()
	:m_world(b2Vec2(0.0f, -8.0f))
{
	if (m_contactListener == nullptr)
	{
		m_contactListener = new MyContactListener;
	}

	m_loadWorld = false;
	int spawn = rand() % 80;

	m_player[0].Init(&m_world, glm::vec2(spawn, 24), glm::vec2(2.0, 5.0), 0);
	m_player[1].Init(&m_world, glm::vec2(spawn, 24), glm::vec2(2.0, 5.0), 1);
	m_player[2].Init(&m_world, glm::vec2(spawn, 24), glm::vec2(2.0, 5.0), 2);
	m_player[3].Init(&m_world, glm::vec2(spawn, 24), glm::vec2(2.0, 5.0), 3);
}

GamePhysics::~GamePhysics()
{
	Free();
	m_powerupHandler.Free();
	m_skullHandler.Free();
}

void GamePhysics::EnterWorld(std::string levelName)
{
	m_texture[0] = m_textureHandler.Import(".\\Assets\\Textures\\health.jpg");
	m_texture[1] = m_textureHandler.Import(".\\Assets\\Textures\\healthbackground.jpg");
	m_texture[2] = m_textureHandler.Import(".\\Assets\\Textures\\sight.png");

	//Player arrows
	m_texture[3] = m_textureHandler.Import(".\\Assets\\Textures\\red.png");
	m_texture[4] = m_textureHandler.Import(".\\Assets\\Textures\\orange.png");
	m_texture[5] = m_textureHandler.Import(".\\Assets\\Textures\\blue.png");
	m_texture[6] = m_textureHandler.Import(".\\Assets\\Textures\\green.png");
	m_texture[7] = m_textureHandler.Import(".\\Assets\\Textures\\spark2.png");

	m_floorCollider.CreateBoundingBoxes(&m_world, levelName);


	if (m_powerupHandler.GetSpawn())
	{
		m_powerupHandler.Free();
	}

	if (m_skullHandler.GetSpawn())
	{
		m_skullHandler.Free();
	}

	//at global scope

	//in FooTest constructor
	m_world.SetContactListener(m_contactListener);

	//Set spawn position of player AND SIZE OF SPRITE BOX
	m_powerupHandler.Init(&m_world);
	m_skullHandler.Init(&m_world);

	//player fixture is of type PLAYER
	m_loadWorld = true;
}


void GamePhysics::Update()
{
	m_world.Step(1.0f / 30.0f, 6, 2);

	for (int i = 0; i < 4; i++)
	{
		m_player[i].Update(m_player);

		if (m_player[i].GetDead() && m_player[i].GetSkullCheck())
		{
			m_skullHandler.SpawnSkull(m_player[i].GetDeathPos(), ScoreManager::GetScore(m_player[i].GetControllerID()) / 10);
			ScoreManager::AddScore(m_player[i].GetControllerID(), -(ScoreManager::GetScore(m_player[i].GetControllerID()) / 10));
			m_player[i].SetSkullCheck(false);
		}





		m_powerupHandler.Update();
		m_skullHandler.Update();

		//Update player bounding box sprite position to the position of the player mesh
	}
		m_world.Step(1.0f / 20.0f, 8, 5);
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
	delete m_texture[0];
	delete m_texture[1];
	delete m_texture[2];
	delete	m_texture[3];
	delete m_texture[4];
	delete m_texture[5];
	delete m_texture[6];
	delete m_texture[7];
}


void GamePhysics::Render(Camera camera)
{
	//	m_transf.SetPosition(42.0, 24.0, -0.0);
	m_floorCollider.DrawCollider(camera);

	for (int i = 0; i < 4; i++) {




		// PLAYER RENDER
		m_player[i].Render(camera);
		//

		//LASER SIGHT
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
		glBlendFunc(GL_ONE, GL_SRC0_ALPHA);
		m_player[i].GetLaserSight()->SetAlbedoID(m_texture[2]->GetTexture());
		m_player[i].GetLaserSight()->Render(camera);
		glDisable(GL_BLEND);




	}

	m_powerupHandler.Render(camera);
	m_skullHandler.Render(camera);



	for (int i = 0; i < 4; i++) {



		//Player Arrow
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_player[i].GetPlayerArrow()->SetAlbedoID(m_texture[i + 3]->GetTexture());
		m_player[i].GetPlayerArrow()->Render(camera);
		glDisable(GL_BLEND);

		//MUZZLE FLASH/////////////////////////////
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		m_player[i].GetMuzzleFlash()->SetAlbedoID(m_texture[7]->GetTexture());
		m_player[i].GetMuzzleFlash()->Render(camera);
		glDisable(GL_BLEND);
		////////////////////////////////////////////

		for (int i = 0; i < 4; i++)
		{

			m_player[i].GetHealthBarBackground()->SetAlbedoID(m_texture[1]->GetTexture());
			m_player[i].GetHealthBarBackground()->Render(camera);

			m_player[i].GetHealthBar()->SetAlbedoID(m_texture[0]->GetTexture());
			m_player[i].GetHealthBar()->Render(camera);




		}

	}
}