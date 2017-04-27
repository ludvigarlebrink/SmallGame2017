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
	m_projectiles.clear();
}

void Weapon::SetProjectileType(float restitution, float friction, float damping, float density, float fireRate, int clearRate)
{
	m_restitution = restitution;
	m_friction = friction;
	m_damping = damping;
	m_density = density;
	m_fireRate = fireRate;
	m_clearRate = clearRate;
	m_projectileCounter = 0;

}

void Weapon::Update(glm::vec3 playerPos, b2Vec2 force)
{
	m_prefabGun->SetPosition(playerPos);
	m_time += TimeManager::Get()->GetDeltaTime();

	DeleteProjectile();

}

void Weapon::DeleteProjectile()
{
	if (m_time > (float)m_clearRate)
	{
		for (int i = 0; i < m_projectiles.size(); i++)
		{
			m_projectiles[i]->GetBox().getBody()->GetWorld()->DestroyBody(m_projectiles[i]->GetBox().getBody());
		}
		m_projectiles.clear();
		m_projectileCounter = 0;
	}
}

Projectile * Weapon::ReuseLast()
{
	return m_projectiles[0];
}

void Weapon::Render(Camera camera)
{
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->Update();
		m_projectiles[i]->Render(camera);
		glUseProgram(0);
		m_prefabGun->Update();
		m_prefabGun->Render(camera);
		glUseProgram(0);
	}
}

void Weapon::Shoot(b2Vec2 force, b2World * world, glm::vec3 playerPos)
{
	if (m_projectiles.size() < m_clearRate)
	{
		//create new projectile
		Projectile* projectile = nullptr;
		projectile = new Projectile;
		projectile->InitProjectile(world, glm::vec2(m_prefabGun->GetPosition().x, m_prefabGun->GetPosition().y),
			glm::vec2(m_prefabProjectile->GetScale().x, m_prefabProjectile->GetScale().y),
			m_restitution, m_friction, m_damping, m_density, m_fireRate, true,  m_prefabProjectile);

		projectile->AddForce(force);
		m_projectiles.push_back(projectile);

	}
	else if (m_projectiles.size() == m_clearRate)
	{
		if (m_projectileCounter >= m_clearRate)
		{
			m_projectileCounter = 0;
		}
		if (m_projectileCounter < m_clearRate)
		{
			//reuse projectile
			m_projectiles[m_projectileCounter]->GetBox().getBody()->GetWorld()->DestroyBody(m_projectiles[m_projectileCounter]->GetBox().getBody());
			m_projectiles[m_projectileCounter]->InitProjectile(world, glm::vec2(m_prefabGun->GetPosition().x, m_prefabGun->GetPosition().y),
				glm::vec2(m_prefabProjectile->GetScale().x, m_prefabProjectile->GetScale().y),
				m_restitution, m_friction, m_damping, m_density, m_fireRate, false,  m_prefabProjectile);
			m_projectiles[m_projectileCounter]->GetPrefab()->SetPosition(m_prefabGun->GetPosition());
			m_projectiles[m_projectileCounter]->AddForce(force);
			
			m_projectileCounter++;
		}
	}
}

bool Weapon::FireRate(float rate)
{

	std::cout << "timer: " << m_time << " rate " << rate << std::endl;

	if (m_time >= rate)
	{
		m_time = 0;
		return true;
	}

	return false;
}
