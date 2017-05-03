#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "PrefabManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "TextureHandler.h"
#include "Box.h"


class Projectile
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
	void AddForce(b2Vec2 force);
	void SetFired(bool fired);

	//::.. GET FUNCTIONS ..:://
	int GetLife();
	Prefab* GetPrefab();
	Box GetBox();
	bool GetFired();

	//::.. OTHER FUNCTIONS ..:://
	void Update();
	void Render(Camera camera);
	void StartContact();
	void EndContact();


private:
	Prefab*		m_prefab;
	Box			m_box;
	float		m_fireRate;
	float		m_time;
	int			m_life;
	TextureHandler m_texhandler;
	Texture m_texture;

	GLfloat m_rotationUpdate;
	Sprite m_bulletSprite;
	GLfloat m_bulletScale;
	bool m_isBullet;
	bool m_fired;
	bool m_contact;
	
	enum _entityCategory {
		BOUNDARY = 0x0001,
		PLAYER = 0x0002,
		PROJECTILE = 0x0004,
		FRIENDLY_AIRCRAFT = 0x0008,
		ENEMY_AIRCRAFT = 0x0010,
	};

};

#endif