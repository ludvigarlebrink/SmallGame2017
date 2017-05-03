#ifndef __WEAPON_H__
#define __WEAPON_H__


#include "Projectile.h"
#include "ParticleSystem.h"
#include "String.h"

class Weapon
{
public:
	//::.. CONSTRUCTORS/DESTRUCTOR ..:://
	Weapon();
	Weapon(Prefab * gun, Prefab * projectile);
	Weapon(Prefab * gun);
	virtual ~Weapon();

	void SetProjectileType(float restitution, float friction, float damping,
		float density, float fireRate, int clearRate);

	Projectile * ReuseLast();
	void Render(Camera camera);
	void Update(glm::vec3 playerPos, b2Vec2 force);
	void DeleteProjectile();
	void InitParticleSystem(std::string shadername, glm::vec4 col, GLfloat size, const int nrOf);
	//::.. SET FUNTIONS ..:://
	void Shoot(b2Vec2 force, b2World * world, glm::vec3 playerPos);
	void RenderParticles(Camera camera);
	//::.. GET FUNTIONS ..:://

	bool FireRate(float rate);

private:
	Prefab*					m_prefabGun;
	Prefab*					m_prefabProjectile;
	std::vector<Projectile*>m_projectiles;
	ParticleSystem m_particles;
	float m_restitution;
	float m_friction; 
	float m_damping;
	float m_density; 
	float m_fireRate;
	float m_time;
	float m_clearTime;
	int	  m_projectileCounter;
	int   m_clearRate;
	bool m_isBullet;
	unsigned int m_counter;

};



#endif // !__WEAPON_H__