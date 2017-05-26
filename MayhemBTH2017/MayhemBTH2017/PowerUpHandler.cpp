#include "PowerUpHandler.h"



PowerUpHandler::PowerUpHandler()
{
}

PowerUpHandler::~PowerUpHandler()
{
	/*for (int i = 0; i < 7; i++)
	{
		delete m_pu[i];
		m_pu.clear();
	}*/
	
}

void PowerUpHandler::Init(b2World * world)
{

	
	m_gameLenght = GameSettings::GetGameLenght();

	m_rate = GameSettings::GetPowerUpSpawnRate();
	m_spawnPerSec = 0.05f;
	m_nrOfSpawns = 10;
	m_spawnTimer = m_gameLenght / (m_gameLenght * m_spawnPerSec * m_rate); // gameLenght / nrOfTotalSpawns

	m_currSpawnNr = 0;

	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		glm::vec2 rl;
		rl.x = rand() % 80 + 2;
		rl.y = rand() % 44 + 2;
		m_randLoc.push_back(rl);

		PowerUp* p = new PowerUp();
		p->Create(world, glm::vec2(m_randLoc[i].x, m_randLoc[i].y));
		m_pu.push_back(p);

		srand(time(NULL));
	}
	m_spawn = true;
}

void PowerUpHandler::Free()
{
	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		m_pu.at(i)->Destroy();
		delete m_pu[i];
	}

	m_pu.clear();
}

bool PowerUpHandler::GetSpawn() const
{
	return m_spawn;
}

void PowerUpHandler::SetSpawn(bool x)
{
	m_spawn = x;
}


void PowerUpHandler::Update()
{
	m_threshold += TimeManager::Get()->GetDeltaTime();

	if (m_threshold >= m_spawnTimer)
	{
		srand(time(NULL));
		m_pu[counter]->RandPosition();
		m_pu[counter]->SetActive(true);
		m_threshold = 0;

		std::cout << "spawn" << std::endl;

		counter++;
		if (counter >= m_nrOfSpawns)
		{
			counter = 0;
		}
	}

	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		if (m_pu[i]->GetActive())
		{
			m_pu[i]->Update();
		}
	}
}

void PowerUpHandler::Render(Camera camera)
{
	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		if (m_pu[i]->GetActive())
		{
			m_pu[i]->Render(camera);
		}
	}
}