#include "Weapon.h"



Weapon::Weapon()
{
	m_prefabGun = nullptr;
	m_muzzleFlash = nullptr;
	m_prefabProjectile = nullptr;
}


Weapon::Weapon(Prefab * gun, Prefab * projectile, int controllerID, glm::vec3 projectileSpawnPoint)
{
	m_collisionpath = "";
	m_prefabGun = nullptr;
	m_muzzleFlash = nullptr;
	m_prefabProjectile = nullptr;

	m_isBullet = false;
	m_prefabGun = gun;
	m_hasParticles = false;
	m_prefabProjectile = projectile;

	m_time = 0;
	m_clearTime = 0;
	m_counter = 0;

	m_projectileSpawnPoint = projectileSpawnPoint;

	m_render = false;

	m_particletimer = 0.0f;
	m_projectileCounter = 0;

	m_controllerID = controllerID;

	m_soundManager = SoundManager::Get();

	m_isRight = true;
}


Weapon::Weapon(Prefab * gun)
{
	if (m_prefabGun != nullptr)
	{
		delete m_prefabGun;
		m_prefabGun = nullptr;
	}

	m_prefabGun = gun;

	m_time = 0;
	m_clearTime = 0;
	m_counter = 0;
	m_isBullet = true;
}


Weapon::~Weapon()
{
	// Check this.
	if (m_prefabGun != nullptr)
	{
		delete m_prefabGun;
		m_prefabGun = nullptr;
	}

	if (m_muzzleFlash != nullptr)
	{
		delete m_muzzleFlash;
		m_muzzleFlash = nullptr;
	}
	if (m_prefabProjectile != nullptr)
	{
		delete m_prefabProjectile;
		m_prefabProjectile = nullptr;
	}

	m_projectiles.clear();

}


void Weapon::SetProjectileType(float restitution, float friction, float damping, float density, float fireRate, int clearRate, int controllerID, float life)
{

	m_life = life;
	m_restitution = restitution;
	m_friction = friction;
	m_damping = damping;
	m_density = density;
	m_fireRate = fireRate;
	m_clearRate = clearRate;
	m_controllerID = controllerID;
	m_hasParticles = false;

}


void Weapon::SetFirePower(GLfloat firepower)
{
	m_firepower = firepower;
}


float Weapon::GetDamage()
{
	return m_damage;
}


void Weapon::SetParticleTexture(Texture* texture)
{
	m_particleTexture = texture;
}


void Weapon::Update(glm::vec3 playerPos, b2Vec2 force, uint32_t controllerID)
{

	m_time += TimeManager::Get()->GetDeltaTime();
	m_clearTime += TimeManager::Get()->GetDeltaTime();

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->Update();

	}

	if (InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_X, controllerID) > 0.300000f)
	{
		m_isRight = true;
	}

	else if (InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_X, controllerID) < -0.300000f)
	{
		m_isRight = false;
	}

	float y = InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y, controllerID);

	if (m_isRight)
	{
		m_force = glm::vec2(-1.0f + abs(y), -y);
		m_force = glm::normalize(m_force);
	}
	else
	{
		m_force = glm::vec2(1.0f - abs(y), -y);
		m_force = glm::normalize(m_force);
	}
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


void Weapon::SetWeaponSound(const char * filepath)
{

	m_soundpath = filepath;

}


void Weapon::SetCollisionSound(const char * filepath)
{
	m_collisionpath = filepath;

}


void Weapon::InitParticleSystem(std::string shadername, glm::vec4 col, GLfloat size, const int nrof, float life)
{
	m_hasParticles = true;
	m_shaderName = shadername;
	m_col = col;
	m_size = size;
	m_nrOf = nrof;
	m_plife = life;

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->InitParticles(shadername, col, size, nrof, life);

	}
}

void Weapon::SetTexture(const char * filepath)
{

	//
}

void Weapon::SetDamage(float damage)
{
	m_damage = damage;

}

Projectile * Weapon::ReuseLast()
{
	return m_projectiles[0];
}


void Weapon::UpdateParticles()
{

}


glm::vec3 Weapon::GetWeaponOffset()
{
	return m_projectileSpawnPoint;
}

float Weapon::GetFireRate()
{
	return m_fireRate;
}

Prefab * Weapon::GetWeaponPre()
{
	return m_prefabGun;
}

void Weapon::Shoot(b2World * world, glm::vec3 pos, int controllerID)
{
	GLfloat firePower = m_firepower;

	firePower *= 10;
	glm::vec2 force = m_force * firePower;

	if (m_projectiles.size() < m_clearRate)
	{
		Projectile* projectile = nullptr;
		projectile = new Projectile();
		//	projectile->InitParticles(m_shaderName, m_col, m_size, m_nrOf, m_plife);
			//create new projectile

		if (m_isBullet == false) {

			m_soundManager->PlaySFX(m_soundpath);

			projectile->InitProjectile(world, glm::vec2(pos.x, pos.y),
				glm::vec2(m_prefabProjectile->GetScale().x, m_prefabProjectile->GetScale().y),
				m_restitution, m_friction, m_damping, m_density, m_fireRate, true, m_prefabProjectile, m_controllerID, m_life);

			projectile->SetHasParticles(m_hasParticles);
			projectile->SetTexture(m_particleTexture);
			projectile->SetCollisionSound(m_collisionpath);
		}

		projectile->AddForce(glm::vec3(force, 0.0f), m_controllerID);
		m_projectiles.push_back(projectile);
	}
	else if (m_projectiles.size() == m_clearRate)
	{
		if (m_projectileCounter == m_clearRate)
			m_projectileCounter = 0;

		if (m_projectileCounter < m_clearRate)
		{
			m_soundManager->PlaySFX(m_soundpath);

			//reuse projectile
			m_projectiles[m_projectileCounter]->SetActive(false);
			m_projectiles[m_projectileCounter]->Update();

			m_projectiles[m_projectileCounter]->InitProjectile(world, glm::vec2(pos.x, pos.y),
				glm::vec2(m_prefabProjectile->GetScale().x, m_prefabProjectile->GetScale().y),
				m_restitution, m_friction, m_damping, m_density, m_fireRate, false, m_prefabProjectile, controllerID, m_life);
			//m_projectiles[m_projectileCounter]->GetPrefab()->SetPosition(m_prefabGun->GetPosition());
			m_projectiles[m_projectileCounter]->AddForce(glm::vec3(force, 0.0f), controllerID);

			m_projectiles[m_projectileCounter]->SetHasParticles(m_hasParticles);
			m_projectiles[m_projectileCounter]->SetTexture(m_particleTexture);
			m_projectiles[m_projectileCounter]->SetCollisionSound(m_collisionpath);

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

		m_projectiles[i]->Update();
		m_projectiles[i]->Render(camera);


	}

}

void Weapon::RenderShadow(Camera camera)
{
	Transform pTransform;

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		pTransform.SetPosition(m_projectiles[i]->GetBox().getBody()->GetPosition().x / 2, m_projectiles[i]->GetBox().getBody()->GetPosition().y / 2, 0);
		m_projectiles[i]->Update();

		m_projectiles[i]->Render(camera);


	}
}
