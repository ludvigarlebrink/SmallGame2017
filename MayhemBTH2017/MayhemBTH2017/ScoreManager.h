#ifndef __SCORE_H__
#define __SCORE_H__


#include "TimeManager.h"


#include <cstdint>


class ScoreManager
{
public:
	ScoreManager();
	virtual ~ScoreManager();
	
	static void Update();
	static void Reset();

	//::.. MODIFY FUNCTIONS ..:://
	static void AddScore(uint32_t score);
	static void AddHitScore();
	static void AddDeath();
	static void AddKill();

	//::.. GET FUNCTIONS ..:://
	static uint32_t GetDeaths();
	static uint32_t GetKills();
	static uint32_t GetCurrKillStreak();
	static uint32_t GetHighestKillStreak();
	static float GetKDRatio();

private:
	struct PlayerScore
	{
		float		hitTimer;

		int32_t		score;
		uint32_t	deaths;
		uint32_t	kills;
		uint32_t	currKillStreak;
		uint32_t	highestKillStreak;
		float		kd;

	};

	static PlayerScore * m_playerScore;
};


#endif // !__SCOREHANDLER_H__