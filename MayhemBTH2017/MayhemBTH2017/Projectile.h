#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "PrefabManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "TextureHandler.h"
#include "Box.h"
#include "ParticleSystem.h"
#include "Collidable.h"


class Projectile : public Collidable
{
public:
	//::.. CONSTRUCTORS ..:://
	Projectile();
	virtual ~Projectile();

	//::.. INIT FUNCTION ..:://
	void InitProjectile(b2World * world, glm::vec2 pos, glm::vec2 scale,
		float restitution, float friction,
		float damping, float density,
		float fireRate, bool startUp, Prefab * prefab, int controllerID, float life);

	void InitBullet(b2World * world, glm::vec2 pos);

	//::.. SET FUNCTIONS ..:://
	void SetLife(float life);
	void AddForce(glm::vec3 force, int controllerID);

	void SetActive(bool active);

	//::.. GET FUNCTIONS ..:://
	float GetLife();
	Prefab* GetPrefab();
	Box GetBox();
	ParticleSystem* m_particles;
	bool GetContact();
	bool IsActive();
	int GetProjectileID();
	float m_particleTimer;
	//::.. OTHER FUNCTIONS ..:://
	void Update();
	void Render(Camera camera);
	void StartContact();
	void EndContact();




private:
	Prefab*		m_prefab;
	Prefab m_prefabPointer;
	Box			m_box;
	float		m_fireRate;
	float		m_time;
	float			m_life;
	float		m_lifeTime;
	bool		m_onGround;

	bool m_renderParticles;
	bool m_hasParticles;
	glm::vec4 m_col;
	std::string m_shadername;
	float m_size;
	float m_nrof;
	float m_particleLife;
	bool m_particlesCreated;

	Transform m_transform;
	GLfloat m_angle;
	Camera	m_camera;
	GLfloat m_rotationUpdate;
	Prefab* m_bulletSprite;
	GLfloat m_bulletScale;
	bool m_isBullet;
	bool m_fired;
	bool m_contact;
	GLfloat tempAngle;
	float m_xAngle;
	float m_yAngle;
	int m_controllerID;

	bool m_active;
	float m_restitution;

	
	enum _entityCategory {
		BOUNDARY = 0x0001,
		PLAYER1 = 0x0002,
		PROJECTILE1 = 0x0004,
		POWERUP = 0x0008,
		PLAYER2 = 0x0016,
		PROJECTILE2 = 0x0032,
	};
};

#endif