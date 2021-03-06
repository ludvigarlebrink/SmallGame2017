#ifndef __APROJECTILE_H__
#define __APROJECTILE_H__

#include "Box.h"

#include "TimeManager.h"

#include <vector>

class AProjectile
{
public:
	AProjectile();
	virtual ~AProjectile();

	void Init(b2World * world, bool startUp, int index);

	void Fire(float rate);

	std::vector<Box> GetProjectileBoxes();


private:
	std::vector<Box> m_projectiles;
	unsigned int	 m_counter;
	float			 m_time;
	b2World*		 m_world;

};

#endif // !__APROJECTILE_H__