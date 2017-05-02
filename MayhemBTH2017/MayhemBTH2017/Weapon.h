#ifndef __WEAPON_H__
#define __WEAPON_H__


#include "Projectile.h"


class Weapon
{
public:
	//::.. CONSTRUCTORS/DESTRUCTOR ..:://
	Weapon();
	Weapon(Prefab * gun, Prefab * projectile);
	Weapon(Prefab * gun);
	virtual ~Weapon();

	void SetProjectileType(float restitution, float friction, float damping,
		float density, float fireRate, int life);
	void Bullet();
	Projectile * ReuseLast();
	void Render(Camera camera);
	void Update(glm::vec3 playerPos);
	void DeleteProjectile();

	//::.. SET FUNTIONS ..:://
	void FireProjectile(b2Vec2 force, b2World * world, glm::vec3 playerPos);
	void FireGun(b2Vec2 force, b2World * world);

	//::.. GET FUNTIONS ..:://

	bool FireRate(float rate);

private:
	Prefab*					m_prefabGun;
	Prefab*					m_prefabProjectile;
	std::vector<Projectile*>m_projectiles;

	GLfloat m_restitution;
	GLfloat m_friction; 
	GLfloat m_damping;
	GLfloat m_density; 
	GLfloat m_fireRate;
	GLfloat m_time;
	GLfloat m_lifetime;
	GLint	m_projectileCounter;
	GLint	m_life;

};



#endif // !__WEAPON_H__
