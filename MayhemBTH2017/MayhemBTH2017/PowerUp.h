#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Box.h"
#include "Prefab.h"
#include "PrefabManager.h"
#include "Collidable.h"
#include <time.h>

class PowerUp : public Collidable
{
public:
	PowerUp();
	virtual ~PowerUp();

	void Create(b2World* world, glm::vec2 pos);

	void Render(Camera camera);

	//::..GET FUNCTIONS..:://
	Box GetBox();
	bool GetActive();
	void CollidedWithPlayer(bool player);

	//::..SET FUNCTIONS..:://
	void SetActive(bool active);

	void RandPosition();

	void Update();

	void Destroy();


private:

	Box m_boundingBox;
	Prefab* m_powerupPrefab;
	glm::vec2 scale;
	bool m_collidedPlayer;
	bool m_active;
	float lifeTime;

	enum _entityCategory {
		BOUNDARY = 0x0001,
		PLAYER1 = 0x0002,
		PROJECTILE1 = 0x0004,
		POWERUP = 0x0008,
		PLAYER2 = 0x0016,
		PROJECTILE2 = 0x0032,
	};

};

#endif // !__POWERUP_H__



