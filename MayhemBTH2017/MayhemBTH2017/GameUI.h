#ifndef __GAMEUI_H__
#define __GAMEUI_H__


#include "UIImage.h"
#include "UIText.h"
#include "Score.h"

#include <cstdint>


class GameUI
{
public:
	GameUI();
	virtual ~GameUI();
	
	void Update(Score::PlayerScore* playerScore);
	void Render();

	//::.. SET FUNCTIONS ..:://
	void SetNumPLayers(uint32_t numPlayers);


private:
	uint32_t	m_numPlayers;

	UIText		m_gameTimer;
	UIText *	m_playerScore;

};


#endif // !__GAMEUI_H__