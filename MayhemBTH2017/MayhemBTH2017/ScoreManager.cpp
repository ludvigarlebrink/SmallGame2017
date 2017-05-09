#include "ScoreManager.h"



ScoreManager::PlayerScore * ScoreManager::m_playerScore = nullptr;

ScoreManager::ScoreManager()
{
	Reset();
}


ScoreManager::~ScoreManager()
{
}

void ScoreManager::Update()
{
	//if (m_hitTimer < 0.001f)
	//{
	//	m_hitTimer = 0;
	//}
	//else
	//{
	//	m_hitTimer -= m_time->GetDeltaTime();
	//}
}

void ScoreManager::Reset()
{
}

void ScoreManager::AddScore(uint32_t id, uint32_t score)
{
	//m_score += score;
}

void ScoreManager::AddHitScore(uint32_t id)
{

}

void ScoreManager::AddDeath(uint32_t id)
{
	//if (m_currKillStreak > m_highestKillStreak)
	//{
	//	m_highestKillStreak = m_currKillStreak;
	//}
	//
	//++m_deaths;
	//m_currKillStreak = 0;
}

void ScoreManager::AddKill(uint32_t id)
{
	m_playerScore[id].kills += 1;
	m_playerScore[id].currKillStreak += 1;
	m_playerScore[id].score += 100 * m_playerScore[id].currKillStreak;


	//++m_kills;
	//++m_currKillStreak;
}

uint32_t ScoreManager::GetDeaths(uint32_t id)
{
	return 0;
}

uint32_t ScoreManager::GetKills(uint32_t id)
{
	return 0;
}

uint32_t ScoreManager::GetCurrKillStreak(uint32_t id)
{
	return 0;
}

uint32_t ScoreManager::GetHighestKillStreak(uint32_t id)
{
	return 0;
}

float ScoreManager::GetKDRatio(uint32_t id)
{
	return 0.0f;
}
