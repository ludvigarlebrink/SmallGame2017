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

void ScoreManager::AddScore(uint32_t score)
{
	//m_score += score;
}

void ScoreManager::AddHitScore()
{

}

void ScoreManager::AddDeath()
{
	//if (m_currKillStreak > m_highestKillStreak)
	//{
	//	m_highestKillStreak = m_currKillStreak;
	//}
	//
	//++m_deaths;
	//m_currKillStreak = 0;
}

void ScoreManager::AddKill()
{
	//++m_kills;
	//++m_currKillStreak;
}

uint32_t ScoreManager::GetDeaths()
{
	return 0;
}

uint32_t ScoreManager::GetKills()
{
	return 0;
}

uint32_t ScoreManager::GetCurrKillStreak()
{
	return 0;
}

uint32_t ScoreManager::GetHighestKillStreak()
{
	return 0;
}

float ScoreManager::GetKDRatio()
{
	return 0.0f;
}
