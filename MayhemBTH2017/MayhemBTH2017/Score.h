#ifndef __SCORE_H__
#define __SCORE_H__


#include <cstdint>


class Score
{
public:
	struct PlayerScore
	{
		int32_t		score;
		uint32_t	deaths;
		uint32_t	kills;
		uint32_t	currKillStreak;
		uint32_t	highestKillStreak;
		float		kd;
	
	
	};

	Score();
	virtual ~Score();

	PlayerScore * GetPlayerScore();

private:
	PlayerScore	*	m_playerScore;

};


#endif // !__SCOREHANDLER_H__