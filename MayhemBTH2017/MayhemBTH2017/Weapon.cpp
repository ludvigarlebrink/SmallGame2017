#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(Prefab * gun, Prefab * projectile, int controllerID)
{
	

	m_isBullet = false;
	m_prefabGun = gun;
	m_hasParticles = false;
	m_prefabProjectile = projectile;

	m_time = 0;
	m_clearTime = 0;
	m_counter = 0;


	m_render = false;

	m_particletimer = 0.0f;
	m_projectileCounter = 0;

	m_controllerID = controllerID;

	m_soundManager = SoundManager::Get();
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

void Weapon::SetParticleTexture(Texture texture) {

	
	m_particleTexture = texture;



}

void Weapon::Update(glm::vec3 playerPos, b2Vec2 force)
{
	//m_prefabGun->SetPosition(playerPos);
	m_time += TimeManager::Get()->GetDeltaTime();
	m_clearTime += TimeManager::Get()->GetDeltaTime();

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->Update();
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


void Weapon::UpdateParticles() {



}

float Weapon::GetFireRate()
{
	return m_fireRate;
}

void Weapon::Shoot(b2World * world, glm::vec3 pos, int controllerID)
{
	GLfloat firePower = m_firepower;



	glm::vec2 force = glm::vec2(InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_X, controllerID), InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y, controllerID));

	if (abs(force.x) > 0.3f || abs(force.y) > 0.3f)
	{
		m_previousForce = glm::normalize(force);
	}
	else
	{
		if (m_previousForce.x < -0.3f)
		{
			m_previousForce = glm::vec2(1.0f, -0.1f);
		}
		else
		{
			m_previousForce = glm::vec2(-1.0f, -0.0f);
		}
	}

	firePower *= -10;
	m_previousForce *= firePower;


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
		}

		Camera camera;
		Transform temptransform;


		projectile->AddForce(glm::vec3(m_previousForce, 0.0f), m_controllerID);



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
			m_projectiles[m_projectileCounter]->AddForce(glm::vec3(m_previousForce, 0.0f), controllerID);

			m_projectiles[m_projectileCounter]->SetHasParticles(m_hasParticles);
			m_projectiles[m_projectileCounter]->SetTexture(m_particleTexture);

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
