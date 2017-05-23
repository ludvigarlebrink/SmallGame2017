#include "PowerUpHandler.h"



PowerUpHandler::PowerUpHandler()
{
}

PowerUpHandler::~PowerUpHandler()
{
	
}

void PowerUpHandler::Init(b2World * world)
{

	m_world = world;

	m_gameLenght = GameSettings::GetGameLenght();

	m_rate = GameSettings::GetPowerUpSpawnRate();
	m_spawnPerSec = m_gameLenght / (2 * m_rate);
	m_nrOfSpawns = (m_gameLenght / 2) * m_rate;

	m_currSpawnNr = 0;

	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		srand(i * time(NULL));

		glm::vec2 rl;
		rl.x = rand() % 80 + 2;
		rl.y = rand() % 44 + 2;
		m_randLoc.push_back(rl);
		
		PowerUp * pu = new PowerUp();
		pu->Create(m_world, glm::vec2(m_randLoc[i].x, m_randLoc[i].y));
		m_pu.push_back(pu);

		for (int i = 0; i < 5; i++)
		{
			//relocate


		}
	}
	m_spawn = true;
}


void PowerUpHandler::Update()
{
	m_gameLenght -= TimeManager::Get()->GetDeltaTime();
	m_threshold += TimeManager::Get()->GetDeltaTime();
	std::cout << m_gameLenght;

	//Spawn

	if (m_threshold > m_spawnPerSec && m_gameLenght > 0.0)
	{
		m_pu[m_currSpawnNr]->SetActive(true);
		m_currSpawnNr++;
		m_threshold = 0;
	}
	
	for (int i = 0; i <= m_currSpawnNr; i++)
	{
		if (m_pu[i]->GetActive())
		{
			m_pu[i]->Update();
		}
	}
}

void PowerUpHandler::Render(Camera camera)
{
	for (int i = 0; i <= m_currSpawnNr; i++)
	{
		if (m_pu[i]->GetActive())
		{
			m_pu[i]->Render(camera);
		}
	}
}

void PowerUpHandler::Destroy()
{
	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		m_pu[i]->SetActive(false);
		delete m_pu[i];
		m_pu[i] = NULL;
	}
}
