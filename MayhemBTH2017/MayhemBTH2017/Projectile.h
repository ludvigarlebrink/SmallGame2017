#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "PrefabManager.h"
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
		float fireRate, Prefab * prefab);

	//::.. SET FUNCTIONS ..:://
	void SetLife(int life);
	void AddForce(b2Vec2 force);

	//::.. GET FUNCTIONS ..:://
	int GetLife();

	//::.. OTHER FUNCTIONS ..:://
	void Update();
	void Render(Camera camera);



private:
	Prefab*		m_prefab;
	Box			m_box;
	float		m_fireRate;
	float		m_time;
	int			m_life;
	GLfloat m_rotationUpdate;

};

#endif