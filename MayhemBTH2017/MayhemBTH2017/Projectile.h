#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "PrefabManager.h"
#include "Box.h"


class Projectile
{
public:
	//::.. CONSTRUCTORS ..:://
	Projectile();
	virtual ~Projectile();

	void InitProjectile(b2World * world, glm::vec2 pos, glm::vec2 scale,
		float restitution, float friction,
		float damping, float density,
		float fireRate, Prefab * prefab);

	void Update();

	void Render(Camera camera);



private:
	Prefab*		m_prefab;
	Box			m_box;
	float		m_fireRate;

};

#endif