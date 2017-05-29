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
#include "GameSettings.h"
#include "SoundManager.h"
#include "AtomicBomb.h"
#include "LevelSelector.h"
#include "LevelHandler.h"
#include "StateManager.h"


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
		SELECT_LEVEL,
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
	void SelectLevel();
	void LoadNextLevel();
	void GameOver();

private:
	InputManager *	m_input;

	GamePhysics *	m_world;

	bool		m_isPaused;
	bool		m_playerReady[MAX_PLAYERS];

	uint32_t	m_gameMode;
	uint32_t	m_currState;
	uint32_t	m_numPlayers;
	Timer		m_timer;

	GameUI			m_gameUI;
	LevelSelector	m_levelSelector;

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
	GameSettings * m_gameSettings;
	SoundManager * m_soundManager;

	// TMP ATOMIC BOMB

	AtomicBomb m_atomicBomb;
};


#endif // !__GAMESYSTEM_H__