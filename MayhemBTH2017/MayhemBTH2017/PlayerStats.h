#ifndef __SCORE_H__
#define __SCORE_H__


#include "TimeManager.h"


#include <cstdint>


class PlayerStats
{
public:
	PlayerStats();
	virtual ~PlayerStats();
	
	void Update();
	void Reset();

	//::.. MODIFY FUNCTIONS ..:://
	void AddScore(uint32_t score);
	void AddHitScore();
	void AddDeath();
	void AddKill();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetDeaths();
	uint32_t GetKills();
	uint32_t GetCurrKillStreak();
	uint32_t GetHighestKillStreak();
	float GetKDRatio();

private:
	TimeManager *	m_time;

	float		m_hitTimer;

	int32_t		m_score;
	uint32_t	m_deaths;
	uint32_t	m_kills;
	uint32_t	m_currKillStreak;
	uint32_t	m_highestKillStreak;
	float		m_kd;

};


#endif // !__SCOREHANDLER_H__