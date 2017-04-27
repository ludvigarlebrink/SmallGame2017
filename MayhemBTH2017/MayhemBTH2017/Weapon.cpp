#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(Prefab * gun, Prefab * projectile)
{
	m_prefabGun = gun;
	m_prefabProjectile = projectile;
	m_time = 0;
	m_clearTime = 0;
}


Weapon::~Weapon()
{
}

void Weapon::SetProjectileType(float restitution, float friction, float damping, float density, float fireRate)
{
	m_restitution = restitution;
	m_friction = friction;
	m_damping = damping;
	m_density = density;
	m_fireRate = fireRate;

}

void Weapon::Update(glm::vec3 playerPos)
{
	m_prefabGun->SetPosition(playerPos);

	//ReuseLast();
}

Projectile * Weapon::ReuseLast()
{
	return m_projectiles[m_projectiles.size() - 1];
}



void Weapon::Render(Camera camera)
{
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->Update();
		m_projectiles[i]->Render(camera);
	}
}

void Weapon::Shoot(b2Vec2 force, float rate, b2World * world)
{
	if (ClearRate(10.0f))
	{

	}
	else
	{
		if (FireRate(rate))
		{
			Projectile* projectile = nullptr;
			projectile = new Projectile;
			projectile->InitProjectile(world, glm::vec2(m_prefabGun->GetPosition().x, m_prefabGun->GetPosition().y),
				glm::vec2(m_prefabProjectile->GetScale().x, m_prefabProjectile->GetScale().y),
				m_restitution, m_friction, m_damping, m_density, m_fireRate, m_prefabProjectile);

			projectile->AddForce(force);
			m_projectiles.push_back(projectile);
		}
	}

	
}

bool Weapon::FireRate(float rate)
{
	m_time += TimeManager::Get()->GetDeltaTime();

	std::cout << "timer: " << m_time << " rate " << rate << std::endl;

	if (m_time >= rate)
	{
		m_time = 0;
		return true;
	}

	return false;
}


bool Weapon::ClearRate(float rate)
{
	m_clearTime += TimeManager::Get()->GetDeltaTime();

	std::cout << "timer: " << m_time << " rate " << rate << std::endl;

	if (m_clearTime >= rate)
	{
		m_time = 0;
		return true;
	}

	return false;
}
