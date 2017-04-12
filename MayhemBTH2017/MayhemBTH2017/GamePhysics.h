#ifndef __GAMEPHYSICS_H__
#define __GAMEPHYSICS_H__

#include "Box.h"

class GamePhysics
{
public:
	GamePhysics();
	virtual ~GamePhysics();

	void EnterWorld();

	void Update();

private:
	std::unique_ptr<b2World> m_world;
	Box newBox;
};


#endif // !__GAMEPHYSICS_H__
