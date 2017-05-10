#ifndef __WEAPON_H__
#define __WEAPON_H__


#include "Projectile.h"
#include "ParticleSystem.h"
#include <string.h>

class Weapon
{
public:
	//::.. CONSTRUCTORS/DESTRUCTOR ..:://
	Weapon();
	Weapon(Prefab * gun, Prefab * projectile, int controllerID);
	Weapon(Prefab * gun);
	virtual ~Weapon();

	void SetProjectileType(float restitution, float friction, float damping,
		float density, float fireRate, int clearRate);

	Projectile * ReuseLast();
	void Render(Camera camera);
	void Update(glm::vec3 playerPos, b2Vec2 force);
	void DeleteProjectile();
	void InitParticleSystem(std::string shadername, glm::vec4 col, GLfloat size, const int nrOf, float life);
	//::.. SET FUNTIONS ..:://
	void Shoot(GLfloat firePower, b2World * world, glm::vec3 pos, int controllerID);
	void UpdateParticles();
	//::.. GET FUNTIONS ..:://

	bool FireRate(float rate);

private:
	Prefab*					m_prefabGun;
	Prefab*					m_prefabProjectile;
	std::vector<Projectile*>m_projectiles;

	glm::vec4 m_col;
	std::string m_shadername;
	float m_size;
	float m_nrof;
	float m_life;
	bool m_particlesCreated;

	ParticleSystem* m_particles;
	float m_restitution;
	glm::vec2 m_previousForce;
	float m_friction;
	AShader m_particleDrawShader;
	AShader m_particlePhysicsShader;
	float m_damping;
	float m_density;
	float m_fireRate;
	float m_time;
	float m_particleTimer;
	float m_clearTime;
	int	  m_projectileCounter;
	int   m_clearRate;
	bool m_isBullet;
	int  m_controllerID;
	unsigned int m_counter;

};



#endif // !__WEAPON_H__
