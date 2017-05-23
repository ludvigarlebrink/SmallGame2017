#ifndef __POWERUPHANDLER_H__
#define __POWERUPHANDLER_H__

#include "PowerUp.h"
#include "Player.h"
#include "TimeManager.h"
#include "GameSettings.h"

#include <stdlib.h>
#include <time.h>

class PowerUpHandler
{
public:
	PowerUpHandler();
	virtual ~PowerUpHandler();

	void Init(b2World * world);

	void Update();

	void Render(Camera camera);

	void Destroy();

private:

	b2World * m_world;

	float m_threshold;
	float m_gameLenght;
	float m_spawnPerSec;
	int m_rate;
	int m_nrOfSpawns;
	int m_currSpawnNr;

	std::vector <PowerUp*> m_pu;
	std::vector <glm::vec2> m_randLoc;

	bool m_spawn;
};


#endif // !__POWERUPHANDLER_H__


