#ifndef __WEAPON_H__
#define __WEAPON_H__


#include "Projectile.h"
#include "ParticleSystem.h"
#include "SoundManager.h"
#include "String.h"

class Weapon
{
public:
	//::.. CONSTRUCTORS/DESTRUCTOR ..:://
	Weapon();
	Weapon(Prefab * gun, Prefab * projectile, int controllerID);
	Weapon(Prefab * gun);
	virtual ~Weapon();

	void SetProjectileType(float restitution, float friction, float damping,
		float density, float fireRate, int clearRate, int controllerID, float life);

	Projectile * ReuseLast();
	void Render(Camera camera);
	void RenderShadow(Camera camera);
	void Update(glm::vec3 playerPos, b2Vec2 force);
	void DeleteProjectile();
	void InitParticleSystem(std::string shadername, glm::vec4 col, GLfloat size, const int nrof, float life);
	//::.. SET FUNTIONS ..:://
	void Shoot(GLfloat firePower, b2World * world, glm::vec3 pos, int controllerID);
	void UpdateParticles();
	void SetRocketLauncher(bool is);
	void SetExplosion(bool explosion);
	//::.. GET FUNTIONS ..:://
	float GetFireRate();
	bool FireRate(float rate);
	bool IsRocketLauncher();
	b2Vec2 GetFiredCurrentProjectilePos();
	bool GetExplosion();

	std::vector<Projectile*> GetProjectiles();

private:
	b2Vec2 GetCurrentProjectilePosition();
	Prefab*					m_prefabGun;
	Prefab*					m_prefabProjectile;
	std::vector<Projectile*>m_projectiles;
	ParticleSystem m_particles;
	float m_restitution;
	glm::vec2 m_previousForce;
	float m_friction; 
	float m_damping;
	float m_density; 
	float m_fireRate;
	float m_time;
	float m_clearTime;
	int	  m_projectileCounter;
	int   m_clearRate;
	bool m_isBullet;
	int  m_controllerID;
	unsigned int m_counter;
	float m_life;
	bool  m_rocketLauncher;
	bool m_reuse;
	b2Vec2 m_currentProjectilePosition;
	bool   m_explosion;

	SoundManager * m_soundManager;
};



#endif // !__WEAPON_H__
