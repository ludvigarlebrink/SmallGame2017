#include "Projectile.h"



Projectile::Projectile()
{
	//m_particles = new ParticleSystem(".\\Assets\\GLSL\\GeometryPass", glm::vec3(20, 20, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 1.0f, 500, 5.0f);

	m_time = 0.0;
	m_rotationUpdate = 0.0f;
	m_renderParticles = false;
	m_hasParticles = false;
	m_particleTimer = 0;
}


Projectile::~Projectile()
{
}

void Projectile::InitProjectile(b2World * world, glm::vec2 pos, glm::vec2 scale, float restitution, float friction, float damping, float density, float fireRate, bool startUp, Prefab * prefab, int controllerID, float life)
{
	m_isBullet = false;

	m_contact = false;

	m_prefabPointer = *prefab;

	m_active = true;

	m_life = life;

	m_lifeTime = 0;

	b2Filter filter;

	if (controllerID == 0)
	{
		filter.categoryBits = PROJECTILE1;
		filter.maskBits = BOUNDARY | PLAYER2;
	}
	else if (controllerID == 1)
	{
		filter.categoryBits = PROJECTILE2;
		filter.maskBits = PLAYER1 | BOUNDARY;
	}

	m_controllerID = controllerID;

	m_box.InitDynamic(world, pos, glm::vec2(m_prefabPointer.GetScale().x, m_prefabPointer.GetScale().y));
	m_box.getBody()->SetUserData(this);
	m_box.getFixture()->SetRestitution(restitution);
	m_box.getFixture()->SetFriction(friction);
	m_box.getFixture()->SetDensity(density);
	m_box.getBody()->SetLinearDamping(damping);
	m_box.getFixture()->SetFilterData(filter);
	m_box.getBody()->ResetMassData();

}



void Projectile::InitBullet(b2World * world, glm::vec2 spawnPos)
{
	m_isBullet = true;
	m_bulletScale = 2;

	m_active = true;

	//m_bulletSprite = PrefabManager::Instantiate("Candle", nullptr, nullptr, 0, "Candle");//PrefabManager::InstantiateSprite("RifleProjectile");

	m_box.InitDynamic(world, spawnPos, glm::vec2(2, 0.8));
	m_box.getBody()->SetUserData(this);
	m_box.getFixture()->SetRestitution(0.0);
	m_box.getFixture()->SetFriction(1.0);
	m_box.getFixture()->SetDensity(1.0);
	m_box.getBody()->SetLinearDamping(0.0);

	//Collision info
	b2Filter filter;
	filter.categoryBits = PROJECTILE1;
	filter.maskBits = BOUNDARY;
	m_box.getFixture()->SetFilterData(filter);

}

void Projectile::SetLife(float life)
{
	m_life = life;
}

void Projectile::AddForce(glm::vec3 force, int controllerID)
{

	b2Vec2 boxForce;
	boxForce.x = force.x;
	boxForce.y = force.y;
	boxForce *= 10;

	//	float x = InputManager::Get()->GetAxis(CONTROLLER_AXIS_RIGHT_X, controllerID);
	//	float y = InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y, controllerID);
	//	
	//

	float angle = glm::degrees(atan2(force.y, force.x));


	m_prefabPointer.SetRotation(0, 0, angle - 90);



	m_box.getBody()->ApplyForce(boxForce, m_box.getBody()->GetWorldCenter(), true);
	m_box.getBody()->SetTransform(m_box.getBody()->GetPosition(), (angle));

	tempAngle = m_yAngle;


}

void Projectile::SetActive(bool active)
{
	m_active = active;
}




float Projectile::GetLife()
{
	return m_life;
}

Prefab * Projectile::GetPrefab()
{
	return m_prefab;
}

Box Projectile::GetBox()
{
	return m_box;
}

bool Projectile::GetContact()
{
	return m_contact;
}

bool Projectile::IsActive()
{
	return m_active;
}

int Projectile::GetProjectileID()
{
	return m_controllerID;
}


void Projectile::Update()
{
	m_lifeTime += TimeManager::GetDeltaTime();

	if (m_contact)
	{
		if (m_lifeTime >= m_life)
		{
			GetBox().getBody()->SetActive(false);
			SetActive(false);
			m_renderParticles = true;

			m_lifeTime = 0;
		}
	}

	if (m_active)
	{

		m_rotationUpdate += 10;

		glm::vec3 position = glm::vec3(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, 0.0f);
		m_prefabPointer.SetPosition(position);

		if (m_rotationUpdate > 360)
			m_rotationUpdate = 0;
	}
	else
	{
		if (m_box.IsBody())
		{
			m_box.SetHasBody(false);
			m_box.getBody()->GetWorld()->DestroyBody(m_box.getBody());
		}
	}
}

void Projectile::Render(Camera camera)
{
	if (m_active)
	{

		
		m_prefabPointer.Update();
		m_prefabPointer.Render(camera);
	
	
	}

	if (m_renderParticles) {
		//m_particles->UpdateParticles();
		//m_particles->RenderTransformed();
	}
}

void Projectile::StartContact()
{
	m_contact = true;
}

void Projectile::EndContact()
{
	m_contact = false;
}

