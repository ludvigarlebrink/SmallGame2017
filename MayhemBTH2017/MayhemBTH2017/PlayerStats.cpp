#include "PlayerStats.h"



PlayerStats::PlayerStats()
{
	m_time = TimeManager::Get();
	Reset();
}


PlayerStats::~PlayerStats()
{
}

void PlayerStats::Update()
{
	if (m_hitTimer < 0.001f)
	{
		m_hitTimer = 0;
	}
	else
	{
		m_hitTimer -= m_time->GetDeltaTime();
	}
}

void PlayerStats::Reset()
{
	m_hitTimer = 0;
	m_score = 0;
	m_deaths = 0;
	m_kills = 0;
	m_currKillStreak = 0;
	m_highestKillStreak = 0;
	m_kd = 0;
}

void PlayerStats::AddScore(uint32_t score)
{
	m_score += score;
}

void PlayerStats::AddHitScore()
{

}

void PlayerStats::AddDeath()
{
	if (m_currKillStreak > m_highestKillStreak)
	{
		m_highestKillStreak = m_currKillStreak;
	}

	++m_deaths;
	m_currKillStreak = 0;
}

void PlayerStats::AddKill()
{
	++m_kills;
	++m_currKillStreak;
}

uint32_t PlayerStats::GetDeaths()
{
	return m_deaths;
}

uint32_t PlayerStats::GetKills()
{
	return m_kills;
}

uint32_t PlayerStats::GetCurrKillStreak()
{
	return m_currKillStreak;
}

uint32_t PlayerStats::GetHighestKillStreak()
{
	return m_highestKillStreak;
}

float PlayerStats::GetKDRatio()
{
	return 0.0f;
}
