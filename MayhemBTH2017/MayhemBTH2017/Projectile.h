#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "PrefabManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "TextureHandler.h"
#include "Box.h"
#include "ParticleEmitter.h"
#include "SoundManager.h"
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
	void SetTexture(Texture* texture);
	void InitBullet(b2World * world, glm::vec2 pos);

	//::.. SET FUNCTIONS ..:://
	void SetLife(float life);
	void AddForce(glm::vec3 force, int controllerID);
	void SetHasParticles(bool has);
	void SetActive(bool active);

	//::.. GET FUNCTIONS ..:://
	float GetLife();
	Prefab* GetPrefab();
	Box GetBox();
	ParticleSystem* m_particles;
	bool GetContactStatus();
	bool IsActive();
	void InitParticles(std::string shadername, glm::vec4 col, GLfloat size, const int nrof, float life);
	int GetProjectileID();
	float m_particleTimer;
	//::.. OTHER FUNCTIONS ..:://
	void Update();
	void Render(Camera camera);
	void RenderShadow(Camera camera);
	void StartContact();
	void EndContact();
	bool GetContact();
	void CollisionTimer();
	void CollisionTrue();
	void SetCollisionSound(const char* filepath);



private:
	Prefab*		m_prefab;
	Prefab m_prefabPointer;
	GLuint m_texID;
	const char* m_collisionSoundPath;
	ParticleEmitter emitter;
	ParticleEmitter trailEmitter;
	ParticleSystem* m_trailParticles;
	bool m_renderSmoke;
	Texture* m_texture;
	SoundManager * m_soundManager;
	TextureHandler m_textureHandler;
	Box			m_box;
	float		m_fireRate;
	float		m_time;
	float			m_life;
	float		m_lifeTime;
	bool		m_onGround;
	const char* m_texturepath;
	float		m_trailTime;

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
	ParticleEmitter m_emitter;
	bool m_active;
	float m_restitution;
	float m_collisionTimer;
	bool m_collision;
	
	enum _entityCategory {
		BOUNDARY = 0x0001,
		POWERUP = 0x0002,
		PLAYER1 = 0x0004,
		PLAYER3 = 0x0008,
		PLAYER2 = 0x0010,
		PLAYER4 = 0x0020,
		PROJECTILE1 = 0x0040,
		PROJECTILE2 = 0x0080,
		PROJECTILE3 = 0x0100,
		PROJECTILE4 = 0x0120,
	};
};

#endif