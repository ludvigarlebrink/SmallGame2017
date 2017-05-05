#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Box.h"
#include "Sprite.h"
#include "Prefab.h"
#include "PrefabManager.h"
#include "Collidable.h"

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

	void Update();


private:

	Box m_boundingBox;
	Sprite m_sprite;
	Prefab* m_powerupPrefab;

	bool m_collidedPlayer;

	bool m_active;

	enum _entityCategory {
		BOUNDARY = 0x0001,
		PLAYER = 0x0002,
		PROJECTILE = 0x0004,
		POWERUP = 0x0008,
		ENEMY_AIRCRAFT = 0x0010,
	};

};

#endif // !__POWERUP_H__



