#ifndef __GAMESETTINGS_H__
#define __GAMESETTINGS_H__


#include "UIText.h"


class GameSettings
{
public:
	GameSettings();
	virtual ~GameSettings();

	void Update();
	void Render();


private:
	UIText m_gameLenght;
	UIText m_randomizeOrder;

};


#endif // !__GAMESETTINGS_H__