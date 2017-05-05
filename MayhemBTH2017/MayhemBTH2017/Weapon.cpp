#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(Prefab * gun, Prefab * projectile)
{
	m_isBullet = false;
	m_prefabGun = gun;

	m_prefabProjectile = projectile;

	m_time = 0;
	m_clearTime = 0;
	m_counter = 0;

	m_projectileCounter = 0;


	
}

Weapon::Weapon(Prefab * gun)
{
	m_prefabGun = gun;

	m_time = 0;
	m_clearTime = 0;
	m_counter = 0;
	m_isBullet = true;
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

}

void Weapon::Update(glm::vec3 playerPos, b2Vec2 force)
{
	//m_prefabGun->SetPosition(playerPos);
	m_time += TimeManager::Get()->GetDeltaTime();
	m_clearTime += TimeManager::Get()->GetDeltaTime();

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		if (m_projectiles[i]->IsActive() && m_projectiles[i]->GetContact())
		{
			m_projectiles[i]->GetBox().getBody()->SetActive(false);
			m_projectiles[i]->SetActive(false);
		}
	}

	//DeleteProjectile();


}

void Weapon::DeleteProjectile()
{
	if (m_clearTime > (float)m_clearRate)
	{
		for (int i = 0; i < m_projectiles.size(); i++)
		{
			m_projectiles[i]->GetBox().getBody()->GetWorld()->DestroyBody(m_projectiles[i]->GetBox().getBody());
		}
		m_projectiles.clear();
		m_projectileCounter = 0;
		m_clearTime = 0;
	}
}

void Weapon::InitParticleSystem(std::string shadername, glm::vec4 col, GLfloat size, const int nrOf)
{
	ParticleSystem particles(".\\Assets\\GLSL\\GeometryPass", glm::vec3(5, 20, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 5.0f, 577);
	m_particles = particles;


}

Projectile * Weapon::ReuseLast()
{
	return m_projectiles[0];
}


void Weapon::UpdateParticles() {

	m_particles.UpdateParticles();

}

void Weapon::Shoot(GLfloat firePower, b2World * world, glm::vec3 pos)
{
	
	
	glm::vec2 force = glm::vec2(InputManager::Get()->GetAxis(CONTROLLER_AXIS_RIGHT_X), InputManager::Get()->GetAxis(CONTROLLER_AXIS_RIGHT_Y));

	if (abs(force.x) > 0.001f || abs(force.y) > 0.001f)
		force = glm::normalize(force);

	firePower *= -10;
	force *= firePower;


	if (m_projectiles.size() < m_clearRate)
	{
		Projectile* projectile = nullptr;
		projectile = new Projectile();
		//create new projectile

		if (m_isBullet == false) {

			projectile->InitProjectile(world, glm::vec2(pos.x, pos.y),
				glm::vec2(m_prefabProjectile->GetScale().x, m_prefabProjectile->GetScale().y),
				m_restitution, m_friction, m_damping, m_density, m_fireRate, true, m_prefabProjectile);
		
		}

		Camera camera;
		Transform temptransform;
		temptransform.SetPosition(projectile->GetBox().getBody()->GetPosition().x, projectile->GetBox().getBody()->GetPosition().y, 0);
		m_particles.Update(temptransform, camera);

		projectile->AddForce(glm::vec3(force, 0.0f));
		m_projectiles.push_back(projectile);



	}


	if (m_projectiles.size() == m_clearRate)
	{
		if (m_projectileCounter >= m_clearRate)
			m_projectileCounter = 0;

		else if (m_projectileCounter <= m_clearRate)
		{

			//reuse projectile
			m_projectiles[m_projectileCounter]->SetActive(false);
			m_projectiles[m_projectileCounter]->Update();

			m_projectiles[m_projectileCounter]->InitProjectile(world, glm::vec2(pos.x, pos.y),
				glm::vec2(m_prefabProjectile->GetScale().x, m_prefabProjectile->GetScale().y),
				m_restitution, m_friction, m_damping, m_density, m_fireRate, false, m_prefabProjectile);
			//m_projectiles[m_projectileCounter]->GetPrefab()->SetPosition(m_prefabGun->GetPosition());
			m_projectiles[m_projectileCounter]->AddForce(glm::vec3(force, 0.0f));

			m_projectileCounter++;
			
		}

	}




}

bool Weapon::FireRate(float rate)
{


	if (m_time >= rate)
	{
		m_time = 0;
		return true;
	}

	return false;
}
void Weapon::Render(Camera camera)
{
	Transform pTransform;

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		pTransform.SetPosition(m_projectiles[i]->GetBox().getBody()->GetPosition().x / 2, m_projectiles[i]->GetBox().getBody()->GetPosition().y / 2, 0);
		m_projectiles[i]->Update();
		m_projectiles[i]->Render(camera);


	}
	
	m_particles.UpdateParticles();

	m_particles.Update(pTransform, camera);

	m_particles.RenderTransformed();
}
