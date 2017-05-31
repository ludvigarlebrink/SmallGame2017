#ifndef __SKULLHANDLER_H__
#define __SKULLHANDLER_H__

#include "PowerUp.h"
#include "Player.h"
#include "TimeManager.h"
#include "GameSettings.h"

class SkullHandler
{
public:
	SkullHandler();
	virtual ~SkullHandler();

	void Init(b2World * world);
	void Free();

	// Get
	bool GetSpawn() const;
	float GetCurrentSkull();
	std::vector <PowerUp*> GetSkulls();

	// Set
	void SetSpawn(bool value);
	void SetCurrentSkull(float value);

	void Update();
	void SpawnSkull(b2Vec2 pos, uint32_t score);

	void Render(Camera camera);

private:
	std::vector <PowerUp*> m_skulls;
	bool m_spawn = false;
	float m_nrOfSpawns;
	float m_currentSkull = 0;
};

#endif