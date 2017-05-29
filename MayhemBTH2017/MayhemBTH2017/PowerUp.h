#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Box.h"
#include "Sprite.h"
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
	Prefab * GetPrefab();
	bool GetActive();
	void CollidedWithPlayer(bool player);

	//::..SET FUNCTIONS..:://
	void SetActive(bool active);

	void RandPosition();

	void Update();

	void Destroy();


private:

	Box m_boundingBox;
	Sprite m_sprite;
	//Prefab* m_powerupPrefab;

	glm::vec2 scale;

	bool m_collidedPlayer;

	bool m_active;

	enum _entityCategory {
		BOUNDARY = 0x0001,
		PLAYER1 = 0x0002,
		PROJECTILE1 = 0x0004,
		POWERUP = 0x0008,
		PLAYER2 = 0x0016,
		PROJECTILE2 = 0x0032,
		PROJECTILE3 = 0x00256,
		PROJECTILE4 = 0x00512,
		PLAYER3 = 0x0064,
		PLAYER4 = 0x00128,
	};

};

#endif // !__POWERUP_H__



