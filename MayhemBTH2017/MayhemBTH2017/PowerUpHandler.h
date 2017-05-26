#ifndef __POWERUPHANDLER_H__
#define __POWERUPHANDLER_H__

#include "PowerUp.h"
#include "Player.h"
#include "TimeManager.h"
#include "GameSettings.h"
#include <iostream>

#include <stdlib.h>
#include <time.h>

class PowerUpHandler
{
public:
	PowerUpHandler();
	virtual ~PowerUpHandler();

	void Init(b2World * world);
	void Free();

	bool GetSpawn()const;
	void SetSpawn(bool x);

	void Update();

	void Render(Camera camera);

private:


	float m_threshold;
	float m_gameLenght;
	float m_spawnPerSec;
	int m_rate;
	int m_nrOfSpawns;
	int m_currSpawnNr;
	float m_spawnTimer;
	int randomize;
	int lastSpawned;
	int lastSpawned2;

	std::vector <PowerUp*> m_pu;
	std::vector <glm::vec2> m_randLoc;

	bool m_spawn = false;
};


#endif // !__POWERUPHANDLER_H__


