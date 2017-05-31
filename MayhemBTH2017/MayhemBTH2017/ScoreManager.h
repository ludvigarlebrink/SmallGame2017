#ifndef __SCORE_H__
#define __SCORE_H__


#include "TimeManager.h"


#include <cstdint>


class ScoreManager
{
public:
	ScoreManager();
	virtual ~ScoreManager();
	
	void StartUp();
	void ShutDown();

	static void Update();
	static void Reset();

	//::.. MODIFY FUNCTIONS ..:://
	static void AddScore(uint32_t id, uint32_t score);
	static void AddHitScore(uint32_t id);
	static void AddDeath(uint32_t id);
	static void AddKill(uint32_t id);

	//::.. GET FUNCTIONS ..:://
	static int32_t GetScore(uint32_t id);
	static uint32_t GetDeaths(uint32_t id);
	static uint32_t GetKills(uint32_t id);
	static uint32_t GetCurrKillStreak(uint32_t id);
	static uint32_t GetHighestKillStreak(uint32_t id);
	static float GetKDRatio(uint32_t id);
	static bool GetGotScore(uint32_t id);
	static int GetWinnerIndex();

private:
	static ScoreManager * m_instance;

	struct PlayerScore
	{
		float		hitTimer;

		int32_t		score;
		uint32_t	deaths;
		uint32_t	kills;
		uint32_t	currKillStreak;
		uint32_t	highestKillStreak;
		float		kd;
		bool		gotScore;
	};

	static PlayerScore * m_playerScore;
};


#endif // !__SCOREHANDLER_H__