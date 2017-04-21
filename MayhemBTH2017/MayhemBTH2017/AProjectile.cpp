#include "AProjectile.h"



AProjectile::AProjectile()
{
}


AProjectile::~AProjectile()
{
}

void AProjectile::Init(b2World * world, bool startUp, int index)
{
	

	if (startUp)
	{

		Box boxTemp[10];
		m_counter = 0;

		m_time = 0;

		for (int i = 0; i < 10; i++)
		{
			boxTemp[i].initDynamic(world, glm::vec2(0.0, 0.0), glm::vec2(0.5, 0.5));
			m_projectiles.push_back(boxTemp[i]);
		}
	}
	else if(!startUp)
	{
		Box boxTemp;
		boxTemp.initDynamic(world, glm::vec2(0.0, 0.0), glm::vec2(0.5, 0.5));
		m_projectiles[index] = boxTemp;
	}


	
}

void AProjectile::Fire(float rate)
{
	m_time += TimeManager::Get()->GetDeltaTime();
	
	if (m_time >= rate)
	{
		if (m_counter < 10)
		{
			m_projectiles[m_counter].getBody()->ApplyForce(b2Vec2(7, 3), m_projectiles[m_counter].getBody()->GetWorldCenter(), true);

			m_time = 0.0f;
			m_counter++;
		}
		else if(m_counter == 10)
		{
			// here we should put back first shot at the origin
		}
	}
}
