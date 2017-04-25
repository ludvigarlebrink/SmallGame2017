#ifndef __BASICGUN_H__
#define __BASICGUN_H__

#include "AProjectile.h"
#include "Sprite.h"


class BasicGun: public AProjectile
{
public:
	BasicGun(b2World* world, glm::vec2 pos);
	virtual ~BasicGun();

	Box UpdateProjectile(b2Vec2 forceDir, glm::vec2 pos);

	glm::vec2 UpdatePos(b2Vec2 forceDir, glm::vec2 pos);

	glm::vec2 UpdateScale(b2Vec2 forceDir, glm::vec2 pos);


private:
	

};

#endif // !__BASICGUN_H__