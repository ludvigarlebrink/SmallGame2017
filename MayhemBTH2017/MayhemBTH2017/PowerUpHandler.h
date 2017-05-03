#ifndef __POWERUPHANDLER_H__
#define __POWERUPHANDLER_H__

#include "PowerUp.h"
#include "Player.h"
#include "TimeManager.h"

#include <stdlib.h>
#include <time.h>

class PowerUpHandler
{
public:
	PowerUpHandler();
	virtual ~PowerUpHandler();

	void Init(Player p, b2World * world, int rate);

	void Spawn();

	bool CollisionCheck(int index);

	void Update();

	void Render(Camera camera);

private:

	float m_time;
	float m_time2;

	b2World * m_world;
	Player * m_player;

	int m_rate;
	int m_nrOfSpawns;
	std::vector <PowerUp*> m_pu;
	std::vector <glm::vec2> m_randLoc;
	std::vector <int> m_elementBuffer;
	int m_currSpawnNr;
	int temp = 0;

	bool m_contact;

};


#endif // !__POWERUPHANDLER_H__


