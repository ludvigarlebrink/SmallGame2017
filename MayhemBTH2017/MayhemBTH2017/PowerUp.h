#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Box.h"
#include "Sprite.h"
#include "Prefab.h"
#include "PrefabManager.h"

class PowerUp
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

	//::..SET FUNCTIONS..:://
	void SetActive(bool active);

	void Update();


private:

	Box m_boundingBox;
	Sprite m_sprite;
	Prefab* m_powerupPrefab;

	bool m_active;

};

#endif // !__POWERUP_H__



