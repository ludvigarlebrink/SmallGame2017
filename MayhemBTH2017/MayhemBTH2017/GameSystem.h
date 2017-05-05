#ifndef __GAMESYSTEM_H__
#define __GAMESYSTEM_H__


#include "GamePhysics.h"
#include "GameUI.h"
#include "Timer.h"
#include "InputManager.h"
#include "Level.h"


#include <cstdint>
#include <vector>


class GameSystem
{
public:
	static const int MAX_PLAYERS = 4;

	enum GameMode
	{
		QUICK_MATCH
	};

	GameSystem();
	virtual ~GameSystem();

	void Load(uint32_t gameMode);
	void Free();

	void Update();

private:
	enum States
	{
		GAME_SETUP = 0,
		PLAYER_READY,
		INIT_PLAY,
		START_PLAY,
		PLAY,
		LOAD_NEXT_LEVEL,
		GAME_OVER
	};
	
	void PlayerReady();
	void InitPlay();

private:
	InputManager * m_input;

	bool		m_isPaused;
	bool		m_playerReady[MAX_PLAYERS];

	uint32_t	m_gameMode;
	uint32_t	m_currState;
	uint32_t	m_timer;

	uint32_t	m_numPlayers;

	std::vector<Level*>		m_levelQueue;
};


#endif // !__GAMESYSTEM_H__