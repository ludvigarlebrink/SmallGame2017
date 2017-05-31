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
	Weapon(Prefab * gun, Prefab * projectile, int controllerID, glm::vec3 projectileSpawnPoint);
	Weapon(Prefab * gun);
	virtual ~Weapon();

	void SetProjectileType(float restitution, float friction, float damping,
		float density, float fireRate, int clearRate, int controllerID, float life);
	void SetFirePower(GLfloat firepower);
	float GetDamage();
	void SetDamage(float damage);
	Projectile * ReuseLast();
	void Render(Camera camera);
	void RenderShadow(Camera camera);
	void Update(glm::vec3 playerPos, b2Vec2 force);
	void DeleteProjectile();
	void SetWeaponSound(const char* filepath);
	void SetCollisionSound(const char* filepath);
	void SetParticleTexture(Texture* texture);
	void InitParticleSystem(std::string shadername, glm::vec4 col, GLfloat size, const int nrof, float life);
	void SetTexture(const char* filepath);

	void Shoot(b2World * world, glm::vec3 pos, int controllerID);
	void UpdateParticles();

	glm::vec3 GetWeaponOffset();
	

	float GetFireRate();
	Prefab * GetWeaponPre();

	bool FireRate(float rate);

private:

	// WTF IS THIS!
	GLfloat					m_firepower;
	const char*				m_texturePath;
	Prefab*					m_prefabGun;
	Prefab*					m_muzzleFlash;
	Prefab*					m_prefabProjectile;
	std::vector<Projectile*>m_projectiles;
	const char* m_soundpath;
	const char* m_collisionpath;
	TextureManager m_texMan;
	Texture		m_tex;
	bool m_hasParticles;
	ParticleEmitter* m_smokeEmitter;
	float m_restitution;
	glm::vec2 m_previousForce;
	float m_friction;
	float m_damping;
	bool count;
	float m_damage;
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

	Transform m_transform;
	
	std::string				m_shaderName;
	glm::vec3				m_pos;
	glm::vec4				m_col;
	float					m_size;
	bool					m_render;
	int						m_nrOf;
	float					m_plife;
	const char*	m_partTexture;
	TextureHandler m_textureHandler;
	Texture*	m_particleTexture;
	TextureManager m_textureManager;
	SoundManager * m_soundManager;


	//::.. NORMAL FACTORING ..:://
	glm::vec3		m_projectileSpawnPoint;
};



#endif // !__WEAPON_H__
