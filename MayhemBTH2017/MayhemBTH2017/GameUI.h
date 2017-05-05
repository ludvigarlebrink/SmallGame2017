#ifndef __GAMEUI_H__
#define __GAMEUI_H__


#include "VideoManager.h"
#include "UIImage.h"
#include "UIText.h"
#include "PlayerStats.h"

#include <cstdint>
#include <cstdlib>
#include <cstdio>

class GameUI
{
public:
	GameUI();
	virtual ~GameUI();
	
	void Update(PlayerStats * stats, int32_t time);
	void Render();

	//::.. SET FUNCTIONS ..:://
	void SetNumPLayers(uint32_t numPlayers);

private:
	VideoManager *	m_video;

	uint32_t		m_numPlayers;

	UIText			m_gameTimer;
	UIText			m_playerName[4];
	UIText			m_playerScore[4];
};


#endif // !__GAMEUI_H__