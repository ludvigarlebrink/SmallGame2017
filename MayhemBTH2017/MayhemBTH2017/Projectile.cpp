#include "Projectile.h"



Projectile::Projectile()
{
	m_time = 0.0;
	m_rotationUpdate = 0.0f;
}


Projectile::~Projectile()
{
}

void Projectile::InitProjectile(b2World * world, glm::vec2 pos, glm::vec2 scale, float restitution, float friction, float damping, float density, float fireRate, bool startUp, Prefab * prefab)
{
	m_isBullet = false;

	m_prefabPointer = *prefab;

	b2Filter filter;
	filter.categoryBits = PROJECTILE;
	filter.maskBits = PLAYER | BOUNDARY;

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

void Projectile::AddForce(glm::vec3 force)
{

	b2Vec2 boxForce;
	boxForce.x = force.x;
	boxForce.y = force.y;
	boxForce *= 10;
	
	float x = InputManager::Get()->GetAxis(CONTROLLER_AXIS_RIGHT_X);
	float y = InputManager::Get()->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y);
	
	if (abs(x) > 0.1f || abs(y) > 0.1f)
	{
		m_xAngle = x;
		m_yAngle = y;

		if (InputManager::Get()->GetAxis(CONTROLLER_AXIS_RIGHT_X) > 0.001f)
		{
			m_yAngle = 90 + m_yAngle * 90;

		}
		else if (InputManager::Get()->GetAxis(CONTROLLER_AXIS_RIGHT_X) < 0.001f)
		{
			m_yAngle = -90 + m_yAngle * (-90);
	
		}

	}
	m_prefabPointer.SetRotation(0, 0, m_yAngle);

	m_box.getBody()->ApplyForce(boxForce, m_box.getBody()->GetWorldCenter(), true);
	m_box.getBody()->SetTransform(m_box.getBody()->GetPosition(), (m_yAngle));

	tempAngle = m_yAngle;


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


void Projectile::Update()
{
	m_rotationUpdate += 10;

	glm::vec3 position = glm::vec3(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, 0.0f);
	m_prefabPointer.SetPosition(position);

	if (m_rotationUpdate > 360)
		m_rotationUpdate = 0;
}

void Projectile::Render(Camera camera)
{

	m_prefabPointer.Update();
	m_prefabPointer.Render(camera);

}

void Projectile::StartContact()
{
	m_contact = true;
}

void Projectile::EndContact()
{
	m_contact = false;
}
