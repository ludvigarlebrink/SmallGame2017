#include "BasicGun.h"



BasicGun::BasicGun()
{
}

BasicGun::BasicGun(b2World* world, glm::vec2 pos)
{
	Init(world, pos);
}


BasicGun::~BasicGun()
{
}

Box BasicGun::Fire(b2Vec2 forceDir, glm::vec2 pos)
{
	Box shot = UpdateProjectile(forceDir, pos);

	return shot;
}

Box BasicGun::UpdateProjectile(b2Vec2 forceDir, glm::vec2 pos)
{
	Box shot = FireTimer(1.0, pos);

	shot.getBody()->ApplyForce(forceDir, shot.getBody()->GetWorldCenter(), true);

	return shot;
}

