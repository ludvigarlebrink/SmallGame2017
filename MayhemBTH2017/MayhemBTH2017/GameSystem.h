#ifndef __GAMESYSTEM_H__
#define __GAMESYSTEM_H__


#include "GamePhysics.h"
#include "GameUI.h"
#include "Timer.h"
#include "InputManager.h"
#include "Level.h"
#include "UIText.h"
#include "UIImage.h"
#include "TransitionManager.h"

#include "ParticleSystem.h"

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
		INIT_PLAYER_READY,
		PLAYER_READY,
		INIT_PLAY,
		START_PLAY,
		PLAY,
		LOAD_NEXT_LEVEL,
		GAME_OVER
	};
	
	void GameSetup();
	void InitPlayerReady();
	void PlayerReady();
	void InitPlay();
	void StartPlay();
	void Play();
	void LoadNextLevel();
	void GameOver();

private:
	InputManager *	m_input;
	ParticleSystem particles;
	GamePhysics *	m_world;

	bool		m_isPaused;
	bool		m_playerReady[MAX_PLAYERS];

	uint32_t	m_gameMode;
	uint32_t	m_currState;
	uint32_t	m_numPlayers;
	float	m_gameTime;
	Timer		m_timer;

	std::vector<Level*>		m_levelQueue;

	GameUI		m_gameUI;

	// Init Players.
	struct PlayerReadyUI
	{
		UIText	playerName;
		UIText	playerReady;
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	};

	PlayerReadyUI * m_playerReadyUI;

	UIText	m_pressToCont;

	Camera m_camera;
};


#endif // !__GAMESYSTEM_H__