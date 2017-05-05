#ifndef __SCORE_H__
#define __SCORE_H__


#include <cstdint>


class PlayerStats
{
public:
	PlayerStats();
	virtual ~PlayerStats();

private:
	int32_t		m_score;
	uint32_t	m_deaths;
	uint32_t	m_kills;
	uint32_t	m_currKillStreak;
	uint32_t	m_highestKillStreak;
	float		m_kd;

};


#endif // !__SCOREHANDLER_H__