#include "Weapon.h"



Weapon::Weapon()
{


}

Weapon::Weapon(Prefab * gun, Prefab * projectile, int controllerID)
{


	//m_texMan.AddTexture("fireball", ".\\Assets\\Textures\\fireball.png");
	Prefab * flash = PrefabManager::Instantiate("muzzleflash", nullptr, nullptr, 0, "Candle");
	flash->SetShaderProgram(".\\Assets\\GLSL\\BulletShader");

	m_muzzleFlash = flash;

	m_isBullet = false;
	m_prefabGun = gun;
	m_render = false;
	m_prefabProjectile = projectile;

	bool count = false;
	m_particletimer = 0;

	m_time = 0;
	m_clearTime = 0;
	m_counter = 0;

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


}

void Weapon::Update(glm::vec3 playerPos, b2Vec2 force)
{

	//m_prefabGun->SetPosition(playerPos);

	m_time += TimeManager::Get()->GetDeltaTime();

	if (m_particletimer >= 0.0f) {
		m_particletimer += TimeManager::Get()->GetDeltaTime();
	}

	m_clearTime += TimeManager::Get()->GetDeltaTime();

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->Update();


		if (m_projectiles[i]->GetContact()) {





		}
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


void Weapon::InitParticleSystem(std::string shadername, glm::vec4 col, GLfloat size, const int nrof, float life)
{
	m_shaderName = shadername;
	m_col = col;
	m_size = size;
	m_nrOf = nrof;
	m_plife = life;



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

void Weapon::Shoot(GLfloat firePower, b2World * world, glm::vec3 pos, int controllerID)
{




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


		//create new projectile

		if (m_isBullet == false) {
			m_soundManager->Play(SOUND_SFX_EXPLOSION);

			projectile->InitProjectile(world, glm::vec2(pos.x, pos.y),
				glm::vec2(m_prefabProjectile->GetScale().x, m_prefabProjectile->GetScale().y),
				m_restitution, m_friction, m_damping, m_density, m_fireRate, true, m_prefabProjectile, m_controllerID, m_life);

		}



		projectile->AddForce(glm::vec3(m_previousForce, 0.0f), m_controllerID);
		Camera camera;


		//Init projectiles when projectile has contact
		if (projectile->GetContact() == true) {
			m_render = true;

			Transform temptransform;
			temptransform.SetPosition(projectile->GetBox().getBody()->GetPosition().x, projectile->GetBox().getBody()->GetPosition().y, 0);
			m_muzzlePos = temptransform.GetPosition();

			/*	m_particleEmitter = nullptr;
				m_particleEmitter = new ParticleEmitter();*/
			m_particleEmitter->SetParticleSystem(".\\Assets\\GLSL\\GeometryPass", glm::vec3(20, 10, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), 246.8f, 500, 1.0f);

		}

		m_projectiles.push_back(projectile);



	}


	if (m_projectiles.size() == m_clearRate)
	{
		if (m_projectileCounter >= m_clearRate)
			m_projectileCounter = 0;

		else if (m_projectileCounter <= m_clearRate)
		{
			m_soundManager->Play(SOUND_SFX_EXPLOSION);

			//reuse projectile
			m_projectiles[m_projectileCounter]->SetActive(false);
			m_projectiles[m_projectileCounter]->Update();

			m_projectiles[m_projectileCounter]->InitProjectile(world, glm::vec2(pos.x, pos.y),
				glm::vec2(m_prefabProjectile->GetScale().x, m_prefabProjectile->GetScale().y),
				m_restitution, m_friction, m_damping, m_density, m_fireRate, false, m_prefabProjectile, controllerID, m_life);
			//m_projectiles[m_projectileCounter]->GetPrefab()->SetPosition(m_prefabGun->GetPosition());
			m_projectiles[m_projectileCounter]->AddForce(glm::vec3(m_previousForce, 0.0f), controllerID);


			//Init projectiles when projectile has contact
			if (m_projectiles[m_projectileCounter]->GetContact() == true) {
				m_render = true;


				Transform temptransform;
				temptransform.SetPosition(m_projectiles[m_projectileCounter]->GetBox().getBody()->GetPosition().x, m_projectiles[m_projectileCounter]->GetBox().getBody()->GetPosition().y, 0);
				std::cout << "contact2" << std::endl;

				/*m_particleEmitter = nullptr;
				m_particleEmitter = new ParticleEmitter();*/
				m_particleEmitter->SetParticleSystem(".\\Assets\\GLSL\\GeometryPass", glm::vec3(20, 10, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), 246.8f, 500, 1.0f);
			}
			m_projectileCounter++;


		}

	}

	//if (m_particletimer >= 3.0) {
	//	m_particleEmitter = nullptr;
	//	m_render = false;
	//	m_particletimer = -1;
	//}





	//	Camera cam;
		//cam.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
	//	m_muzzleFlash->SetScale(1, 1, 1);
		//m_muzzleFlash->SetPosition(pos.x - (2.0f*InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_X)), m_muzzlePos.y, 0);
		//	m_muzzleFlash->Update();
		//	m_muzzleFlash->Render(cam);


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
	if (m_render) {
		m_particleEmitter->Update();
		m_particleEmitter->Render();
	}
}
