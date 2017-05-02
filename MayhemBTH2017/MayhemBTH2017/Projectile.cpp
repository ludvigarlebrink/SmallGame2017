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

	m_prefab = prefab;

	b2Filter filter;
	filter.categoryBits = PROJECTILE;
	filter.maskBits = PLAYER | BOUNDARY;


	//m_box.initDynamic(world, pos, scale);
	m_box.getBody()->SetUserData(this);
	m_box.getFixture()->SetRestitution(restitution);
	m_box.getFixture()->SetFriction(friction);
	m_box.getFixture()->SetDensity(density);
	m_box.getBody()->SetLinearDamping(damping);
	m_box.getFixture()->SetFilterData(filter);

	m_fireRate = fireRate;
}

void Projectile::InitBullet(b2World * world, glm::vec2 spawnPos)
{
	m_isBullet = true;
	m_bulletScale = 20;
	m_bulletSprite.createSprite(glm::vec2(0), glm::vec2(m_bulletScale));
	m_bulletSprite.Init(".\\Assets\\GLSL\\ColliderShader", 0, 0);


	//m_box.initDynamic(world, spawnPos, glm::vec2(m_bulletScale));
	m_box.getFixture()->SetRestitution(0.0);
	m_box.getFixture()->SetFriction(1.0);
	m_box.getFixture()->SetDensity(1.0);
	m_box.getBody()->SetLinearDamping(0.3);

	//Collision info
	b2Filter filter;
	filter.categoryBits = PROJECTILE;
	filter.maskBits = PLAYER | BOUNDARY;
	m_box.getFixture()->SetFilterData(filter);

	m_fireRate = 0.5;
}

void Projectile::SetLife(int life)
{
	m_life = life;
}

void Projectile::AddForce(b2Vec2 force)
{
	m_box.getBody()->ApplyForce(force, m_box.getBody()->GetWorldCenter(), true);
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
	m_rotationUpdate += 1.0f;

	glm::vec3 position = glm::vec3(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, 0.0f);

	m_bulletSprite.update(glm::vec2(position.x, position.y), glm::vec2(m_bulletScale));

	m_prefab->SetPosition(position);
	m_prefab->SetRotation(0, 0, m_rotationUpdate * 15);
	if (m_rotationUpdate > 360)
		m_rotationUpdate = 0;
}

void Projectile::Render(Camera camera)
{
	if (m_isBullet = false)
		m_prefab->Render(camera);

	else
		m_bulletSprite.draw();
}
