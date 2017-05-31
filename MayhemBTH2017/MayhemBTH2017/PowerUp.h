#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Box.h"
#include "Prefab.h"
#include "PrefabManager.h"
#include "Collidable.h"
#include <time.h>

enum _entityCategory {
	BOUNDARY = 0x0001,
	POWERUP = 0x0002,
	PLAYER1 = 0x0004,
	PLAYER3 = 0x0008,
	PLAYER2 = 0x0010,
	PLAYER4 = 0x0020,
	PROJECTILE1 = 0x0040,
	PROJECTILE2 = 0x0080,
	PROJECTILE3 = 0x0100,
	PROJECTILE4 = 0x0120,
	SKULL = 0x0140,
};

class PowerUp : public Collidable
{
public:
	PowerUp();
	virtual ~PowerUp();

	void Create(b2World* world, glm::vec2 pos);
	void CreateSkull(b2World* world, glm::vec2 pos);

	void Render(Camera camera);

	//::..GET FUNCTIONS..:://
	Box GetBox();
	bool GetActive();
	void CollidedWithPlayer(bool player);
	uint32_t GetScore();
	b2Filter GetFilter();

	//::..SET FUNCTIONS..:://
	void SetActive(bool active);

	void RandPosition();
	void SetPosition(b2Vec2 value);
	void SetScore(uint32_t value);

	void Update();
	void SkullUpdate();

	void Free();


private:

	Box m_boundingBox;
	Prefab* m_powerupPrefab;
	glm::vec2 scale;
	bool m_collidedPlayer;
	bool m_active;
	float lifeTime;
	float scaleTime;
	float deathBound;
	uint32_t m_score;
	b2Filter m_filter;



};

#endif // !__POWERUP_H__



