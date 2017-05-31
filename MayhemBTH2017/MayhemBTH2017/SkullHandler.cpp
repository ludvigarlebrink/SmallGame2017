#include "SkullHandler.h"



SkullHandler::SkullHandler()
{
	// Do nothing
}


SkullHandler::~SkullHandler()
{
	Free();
}

void SkullHandler::Init(b2World * world)
{
	m_nrOfSpawns = 4;
	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		PowerUp* p = new PowerUp;
		p->CreateSkull(world, glm::vec2(999, 999));
		m_skulls.push_back(p);
	}
	m_spawn = true;
}

void SkullHandler::Free()
{
	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		delete m_skulls[i];
	}

	m_skulls.clear();
}

bool SkullHandler::GetSpawn() const
{
	return m_spawn;
}

float SkullHandler::GetCurrentSkull()
{
	return m_currentSkull;
}

std::vector<PowerUp*> SkullHandler::GetSkulls()
{
	return m_skulls;
}

void SkullHandler::SetSpawn(bool value)
{
	m_spawn = value;
}

void SkullHandler::SetCurrentSkull(float value)
{
	m_currentSkull = value;
}

void SkullHandler::Update()
{
	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		if (m_skulls[i]->GetActive())
		{
			m_skulls[i]->Update();
		}
	}
}

void SkullHandler::SpawnSkull(b2Vec2 pos, uint32_t score)
{
	if (m_currentSkull == m_nrOfSpawns)
		m_currentSkull = 0;

	m_skulls[m_currentSkull]->SetPosition(pos);
	m_skulls[m_currentSkull]->SetScore(score);
	m_skulls[m_currentSkull]->SetActive(true);
	m_currentSkull++;

}

void SkullHandler::Render(Camera camera)
{
	for (int i = 0; i < m_nrOfSpawns; i++)
	{
		if (m_skulls[i]->GetActive())
		{
			m_skulls[i]->Render(camera);
		}
	}
}
