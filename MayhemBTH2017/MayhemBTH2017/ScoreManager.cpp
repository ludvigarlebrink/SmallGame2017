#include "ScoreManager.h"


ScoreManager * ScoreManager::m_instance = nullptr;
ScoreManager::PlayerScore * ScoreManager::m_playerScore = nullptr;

ScoreManager::ScoreManager()
{
	Reset();
}


ScoreManager::~ScoreManager()
{

}


void ScoreManager::StartUp()
{
	if (m_instance == nullptr)
	{
		Reset();
	}
}


void ScoreManager::ShutDown()
{

}


void ScoreManager::Update()
{
	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerScore[i].gotScore = false;
	}
}

void ScoreManager::Reset()
{
	m_playerScore = new PlayerScore[4];
	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerScore[i].currKillStreak = 0;
		m_playerScore[i].deaths = 0;
		m_playerScore[i].highestKillStreak = 0;
		m_playerScore[i].hitTimer = 0;
		m_playerScore[i].kd = 0.0f;
		m_playerScore[i].kills = 0;
		m_playerScore[i].score = 0;
	}
}


void ScoreManager::AddScore(uint32_t id, uint32_t score)
{
	m_playerScore[id].score += score;
	m_playerScore[id].gotScore = true;

	if (m_playerScore[id].score < 0)
	{
		m_playerScore[id].score = 0;
	}
}


void ScoreManager::AddHitScore(uint32_t id)
{
	m_playerScore[id].score += 5;
	m_playerScore[id].gotScore = true;
}


void ScoreManager::AddDeath(uint32_t id)
{
	if (m_playerScore[id].currKillStreak > m_playerScore[id].highestKillStreak)
	{
		m_playerScore[id].highestKillStreak = m_playerScore[id].currKillStreak;
	}
	
	m_playerScore[id].deaths += 1;

	m_playerScore[id].currKillStreak = 0;
}


void ScoreManager::AddKill(uint32_t id)
{
	m_playerScore[id].kills += 1;
	m_playerScore[id].currKillStreak += 1;
	m_playerScore[id].score += 100;
	m_playerScore[id].gotScore = true;

	//++m_kills;
	//++m_currKillStreak;
}


int32_t ScoreManager::GetScore(uint32_t id)
{
	return m_playerScore[id].score;
}


uint32_t ScoreManager::GetDeaths(uint32_t id)
{
	return m_playerScore[id].deaths;
}


uint32_t ScoreManager::GetKills(uint32_t id)
{
	return m_playerScore[id].kills;
}


uint32_t ScoreManager::GetCurrKillStreak(uint32_t id)
{
	return m_playerScore[id].currKillStreak;
}


uint32_t ScoreManager::GetHighestKillStreak(uint32_t id)
{
	return 0;
}


float ScoreManager::GetKDRatio(uint32_t id)
{
	return (m_playerScore[id].kills / m_playerScore[id].deaths);
}


bool ScoreManager::GetGotScore(uint32_t id)
{
	return m_playerScore[id].gotScore;
}

int ScoreManager::GetWinnerIndex()
{
	int tmpWinner = 0;

	for (uint32_t i = 0; i < 4; ++i)
	{
		if (m_playerScore[i].score > m_playerScore[tmpWinner].score)
		{
			tmpWinner = i;
		}
	}

	return tmpWinner;
}
