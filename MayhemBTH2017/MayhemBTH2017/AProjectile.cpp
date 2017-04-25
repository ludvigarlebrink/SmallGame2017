#include "AProjectile.h"



AProjectile::AProjectile()
{
}


AProjectile::~AProjectile()
{
}

void AProjectile::Init(b2World * world, glm::vec2 originalPos)
{
	
	m_world = world;

	m_box.initDynamic(world, originalPos, glm::vec2(2, 2));
	
}

Box AProjectile::FireTimer(float rate, glm::vec2 originalPos)
{
	m_time += TimeManager::Get()->GetDeltaTime();

	if (m_time >= rate) {
		
		Init(m_world, originalPos);
		m_time = 0;
	}

	return m_box;
}


Box AProjectile::GetBox()
{
	return m_box;
}

