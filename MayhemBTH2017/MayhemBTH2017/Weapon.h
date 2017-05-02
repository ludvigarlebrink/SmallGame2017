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
		float density, float fireRate, int clearRate);

	Projectile * ReuseLast();
	void Render(Camera camera);
	void Update(glm::vec3 playerPos, b2Vec2 force);
	void DeleteProjectile();

	//::.. SET FUNTIONS ..:://
	void Shoot(b2Vec2 force, b2World * world, glm::vec3 playerPos);

	//::.. GET FUNTIONS ..:://

	bool FireRate(float rate);

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
	int	  m_projectileCounter;
	int   m_clearRate;
	unsigned int m_counter;

};



#endif // !__WEAPON_H__
