#ifndef __WEAPON_H__
#define __WEAPON_H__


#include "Projectile.h"


class Weapon
{
public:
	//::.. CONSTRUCTORS/DESTRUCTOR ..:://
	Weapon();
	Weapon(Prefab * gun, Prefab * projectile);
	virtual ~Weapon();

	void SetProjectileType(float restitution, float friction, float damping,
		float density, float fireRate);

	void Update(glm::vec3 playerPos);

	Projectile * ReuseLast();

	void Render(Camera camera);

	//::.. SET FUNTIONS ..:://
	void Shoot(b2Vec2 force, float rate, b2World * world);

	//::.. GET FUNTIONS ..:://

	bool FireRate(float rate);

	bool ClearRate(float rate);

private:
	Prefab*					m_prefabGun;
	Prefab*					m_prefabProjectile;
	std::vector<Projectile*>m_projectiles;

	float m_restitution;
	float m_friction; 
	float m_damping;
	float m_density; 
	float m_fireRate;
	float m_time;
	float m_clearTime;

};



#endif // !__WEAPON_H__
