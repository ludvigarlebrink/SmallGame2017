#include "PowerUpHandler.h"



PowerUpHandler::PowerUpHandler()
{
}

PowerUpHandler::~PowerUpHandler()
{
}

void PowerUpHandler::Init(Player p, b2World * world, int nrOfSpawns)
{
	m_time = 0;

	m_world = world;
	m_player = &p;
	m_rate = 120 / nrOfSpawns;
	m_nrOfSpawns = nrOfSpawns;

	m_currSpawnNr = -1;
	
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
		m_elementBuffer.push_back(i);

	}
}

void PowerUpHandler::Spawn()
{

}

bool PowerUpHandler::CollisionCheck(int index)
{
	for (b2Contact* contact = m_world->GetContactList(); contact; contact = contact->GetNext())
	{
		if (contact->IsTouching())
		{
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

			if (static_cast<PowerUp*>(bodyUserDataA) || static_cast<PowerUp*>(bodyUserDataB))
			{
				if (static_cast<Player*>(bodyUserDataA) || static_cast<Player*>(bodyUserDataB))
				{
					m_pu[index];
					std::cout << " den nudlar .." << std::endl;
					//m_counter --;
					//replace index 
					return true;
				}
			}
		}
	}
	return false;
}

void PowerUpHandler::Update()
{
	m_time += TimeManager::Get()->GetDeltaTime();

	//Spawn
	if (m_time >= m_rate && m_nrOfSpawns > m_currSpawnNr + 1)
	{
		m_time = 0;
		m_currSpawnNr++;

		m_pu[m_currSpawnNr]->GetBox().getBody()->SetAwake(true);
		m_pu[m_currSpawnNr]->GetBox().getBody()->SetActive(true);

		m_pu[m_currSpawnNr]->SetActive(true);
	}
	
	for (int i = 0; i <= m_currSpawnNr; i++)
	{	
		if (m_pu[i]->GetActive())
		{
			m_pu[i]->Update();
		}

		m_pu[i]->Update();

		if (CollisionCheck(i))
		{
			m_pu[i]->SetActive(false);
		}
	}

	m_time2 += TimeManager::Get()->GetDeltaTime();

	if (m_time2 >= m_rate + 5 && m_nrOfSpawns > m_currSpawnNr + 1)
	{
		m_time2 = 0;
		m_pu[temp]->SetActive(false);
		m_pu[temp]->GetBox().getBody()->SetAwake(false);
		m_pu[temp]->GetBox().getBody()->SetActive(false);
		temp++;
	}
}

void PowerUpHandler::Render(Camera camera)
{
	for (int i = 0; i <= m_currSpawnNr; i++)
	{
		if (m_pu[m_elementBuffer[i]]->GetActive())
		{
			m_pu[i]->Render(camera);
		}
	}
}
