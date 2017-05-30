#ifndef __GAMEUI_H__
#define __GAMEUI_H__


#include "VideoManager.h"
#include "UIImage.h"
#include "UIText.h"
#include "ScoreManager.h"


#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cstdlib>
#include <cstdio>


class GameUI
{
public:
	GameUI();
	virtual ~GameUI();
	
	void Update(float time);

	//::.. SET FUNCTIONS ..:://
	void SetNumPLayers(uint32_t numPlayers);

	void SetPauseDisplay(bool value);
	void SetShowWinner(bool value);

private:
	VideoManager *	m_video;

	uint32_t		m_numPlayers;

	UIText *		m_gameTimer;
	UIText *		m_playerScore[4];
	UIText *		m_winnerText;

	bool			m_pauseDisplay;
	bool			m_showWinner;
};


#endif // !__GAMEUI_H__