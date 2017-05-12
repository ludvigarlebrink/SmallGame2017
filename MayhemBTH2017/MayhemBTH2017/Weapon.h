#ifndef __WEAPON_H__
#define __WEAPON_H__


#include "Projectile.h"
#include "ParticleEmitter.h"
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
	void Update(glm::vec3 playerPos, b2Vec2 force);
	void DeleteProjectile();
	void InitParticleSystem(std::string shadername, glm::vec4 col, GLfloat size, const int nrof, float life);
	//::.. SET FUNTIONS ..:://
	void Shoot(GLfloat firePower, b2World * world, glm::vec3 pos, int controllerID);
	void UpdateParticles();
	//::.. GET FUNTIONS ..:://
	float GetFireRate();

	bool FireRate(float rate);

private:
	Prefab*					m_prefabGun;
	Prefab*					m_muzzleFlash;
	Prefab*					m_prefabProjectile;
	std::vector<Projectile*>m_projectiles;
	TextureManager m_texMan;
	Texture		m_tex;
	ParticleEmitter* m_particleEmitter;
	float m_restitution;
	glm::vec2 m_previousForce;
	float m_friction;
	float m_damping;
	bool count;
	glm::vec3 m_muzzlePos;
	float m_particletimer;
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

	std::string				m_shaderName;
	glm::vec3				m_pos;
	glm::vec4				m_col;
	float					m_size;
	bool					m_render;
	int						m_nrOf;
	float					m_plife;

	SoundManager * m_soundManager;
};



#endif // !__WEAPON_H__
