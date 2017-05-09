#ifndef __GAMESETTINGS_H__
#define __GAMESETTINGS_H__


#include "UIText.h"
#include "InputManager.h"
#include "VideoManager.h"


class GameSettings
{
public:
	static const int NUM_SETTINGS = 4;

	GameSettings();
	virtual ~GameSettings();

	void CreateUI();
	void FreeUI();

	void Update();
	void Render();

	int32_t GetGameLenght();
	int32_t GetPowerUpSpawnRate();
	bool GetRandomizedOrder();

private:
	//::.. HELP FUNCTIONS ..:://

private:
	enum Settings
	{
		GAME_LENGTH = 0,
		POWER_UP_SPAWN_RATE,
		RANDOMIZED_ORDER,
		INSTANT_KILLS
	};

	InputManager * m_input;

	bool m_uiCreated;

	int32_t m_gameLength;
	int32_t m_powerUpsSpawnRate;
	bool m_randomizedOrder;
	bool m_instantKills;

	UIText * m_ui;
	UIText * m_uiV;

	int32_t m_currSel;

};


#endif // !__GAMESETTINGS_H__