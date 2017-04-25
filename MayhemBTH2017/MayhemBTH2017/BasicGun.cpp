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

Box BasicGun::UpdateProjectile(b2Vec2 forceDir, glm::vec2 pos)
{
	Box shot = FireTimer(1.0, pos);

	shot.getBody()->ApplyForce(forceDir, shot.getBody()->GetWorldCenter(), true);

	return shot;
}

glm::vec2 BasicGun::UpdatePos(b2Vec2 forceDir, glm::vec2 pos)
{
	Box shot = UpdateProjectile(forceDir, pos);

	float posX = shot.getBody()->GetPosition().x;
	float posY = shot.getBody()->GetPosition().y;

	return glm::vec2(posX, posY);
}

glm::vec2 BasicGun::UpdateScale(b2Vec2 forceDir, glm::vec2 pos)
{
	Box shot = UpdateProjectile(forceDir, pos);

	float scaleX = shot.getScale().x;
	float scaleY = shot.getScale().y;

	return glm::vec2(scaleX, scaleY);
}


