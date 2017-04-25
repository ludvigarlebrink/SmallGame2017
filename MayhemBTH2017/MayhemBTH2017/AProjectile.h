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

	void Init(b2World * world, glm::vec2 originalPosY);

	Box FireTimer(float rate, glm::vec2 originalPos);

	Box GetBox();


private:
	Box				 m_box;
	unsigned int	 m_counter;
	float			 m_time=0;
	b2World*		 m_world;

};

#endif // !__APROJECTILE_H__