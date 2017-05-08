#include "Projectile.h"



Projectile::Projectile()
{
	m_time = 0.0;
	m_rotationUpdate = 0.0f;
}


Projectile::~Projectile()
{
}

void Projectile::InitProjectile(b2World * world, glm::vec2 pos, glm::vec2 scale, float restitution, float friction, float damping, float density, float fireRate, bool startUp, Prefab * prefab, int controllerID)
{
	m_isBullet = false;

	m_prefabPointer = *prefab;

	m_active = true;

	b2Filter filter;
	filter.categoryBits = PROJECTILE;
	
	if (controllerID == 0)
	{
		filter.maskBits = PLAYER2 | PLAYER3 | PLAYER4 | BOUNDARY;
	}
	else if (controllerID == 1)
	{
		filter.maskBits = PLAYER1 | PLAYER3| PLAYER4 | BOUNDARY;
	}
	else if (controllerID == 2)
	{
		filter.maskBits = PLAYER1 | PLAYER2 | PLAYER4 | BOUNDARY;
	}
	else if (controllerID == 3)
	{
		filter.maskBits = PLAYER1 | PLAYER2 | PLAYER3 | BOUNDARY;
	}

	m_box.InitDynamic(world, pos, scale);
	m_box.getBody()->SetUserData(this);
	m_box.getFixture()->SetRestitution(restitution);
	m_box.getFixture()->SetFriction(friction);
	m_box.getFixture()->SetDensity(density);
	m_box.getBody()->SetLinearDamping(damping);
	m_box.getFixture()->SetFilterData(filter);
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
	filter.categoryBits = PROJECTILE;
	filter.maskBits = BOUNDARY;
	m_box.getFixture()->SetFilterData(filter);
}

void Projectile::SetLife(int life)
{
	m_life = life;
}

void Projectile::AddForce(glm::vec3 force, int controllerID)
{

	b2Vec2 boxForce;
	boxForce.x = force.x;
	boxForce.y = force.y;
	boxForce *= 10;
	
	float x = InputManager::Get()->GetAxis(CONTROLLER_AXIS_RIGHT_X, controllerID);
	float y = InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y, controllerID);
	

	float angle = 90;//atan2(y, x);

	if (abs(x) > 0.2f)
	{
		angle = atan2(y, x);

		angle = glm::degrees(angle);

	//	m_xAngle = x;
	//
	//	if (m_xAngle > 0.001f)
	//	{
	//		m_yAngle = (90 + y) * 90;
	//
	//	}
	//	else if (m_xAngle < 0.001f)
	//	{
	//		m_yAngle =  (y - 90) * (-90);
	//
	//	}


	}


	
	m_prefabPointer.SetRotation(0, 0, angle);

	m_box.getBody()->ApplyForce(boxForce, m_box.getBody()->GetWorldCenter(), true);
	m_box.getBody()->SetTransform(m_box.getBody()->GetPosition(), (angle));

	tempAngle = m_yAngle;


}

void Projectile::SetActive(bool active)
{
	m_active = active;
}

int Projectile::GetLife()
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


void Projectile::Update()
{
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
}

void Projectile::StartContact()
{
	m_contact = true;
}

void Projectile::EndContact()
{
	m_contact = false;
}
