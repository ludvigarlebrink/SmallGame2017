#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "PrefabManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "TextureHandler.h"
#include "Box.h"
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
		float fireRate, bool startUp, Prefab * prefab);

	void InitBullet(b2World * world, glm::vec2 pos);

	//::.. SET FUNCTIONS ..:://
	void SetLife(int life);
	void AddForce(glm::vec3 force);
	void SetFired(bool fired);
	void SetActive(bool active);

	//::.. GET FUNCTIONS ..:://
	int GetLife();
	Prefab* GetPrefab();
	Box GetBox();
	bool GetFired();
	bool GetContact();
	bool IsActive();

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
	int			m_life;
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

	bool m_active;

	
	enum _entityCategory {
		BOUNDARY = 0x0001,
		PLAYER = 0x0002,
		PROJECTILE = 0x0004,
		POWERUP = 0x0008,
		ENEMY_AIRCRAFT = 0x0010,
	};

};

#endif