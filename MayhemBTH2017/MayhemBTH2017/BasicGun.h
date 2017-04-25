#ifndef __BASICGUN_H__
#define __BASICGUN_H__

#include "AProjectile.h"
#include "Sprite.h"


class BasicGun: public AProjectile
{
public:
	BasicGun();
	BasicGun(b2World* world, glm::vec2 pos);
	virtual ~BasicGun();

	Box Fire(b2Vec2 forceDir, glm::vec2 pos);


private:
	Box UpdateProjectile(b2Vec2 forceDir, glm::vec2 pos);
	

};

#endif // !__BASICGUN_H__