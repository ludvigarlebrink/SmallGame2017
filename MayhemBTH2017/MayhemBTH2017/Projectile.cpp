#include "Projectile.h"



Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

void Projectile::InitProjectile(b2World * world, glm::vec2 pos, glm::vec2 scale, float restitution, float friction, float damping, float density, float fireRate, Prefab * prefab)
{
	m_prefab = prefab;

	m_box.initDynamic(world, pos, scale);
	m_box.getFixture()->SetRestitution(restitution);
	m_box.getFixture()->SetFriction(friction);
	m_box.getFixture()->SetDensity(density);
	m_box.getBody()->SetLinearDamping(damping);

	m_fireRate = fireRate;
}

void Projectile::Update()
{
	glm::vec3 position = glm::vec3(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, 0.0f);

	m_prefab->SetPosition(position);
}
