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
	
	m_bulletSprite.CreateSprite(glm::vec2(0), glm::vec2(2, 0.8));
	m_bulletSprite.Init(".\\Assets\\GLSL\\BulletShader", 0, 0);
	
	m_texture = m_texhandler.Import(".\\Assets\\Textures\\bullet.png");

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

	//Fire 
	m_box.getBody()->ApplyForce(boxForce, m_box.getBody()->GetWorldCenter(), true);


	//bounding box rotation
	//m_box.getBody()->SetTransform(m_box.getBody()->GetPosition(), (force.x*force.y));

	//sprite rotation
	//glm::vec3 boundingBoxPos = glm::vec3(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, 0);

	m_transform.SetRotation(glm::vec3(0, 0, 45));

//	m_transform.SetPosition(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, 0);

	glm::vec3 rotation = glm::vec3(0, 0, 20);



	if (m_isBullet == true) {

		m_bulletSprite.Update(m_transform, m_camera);
	}

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
	m_rotationUpdate += 0.01f;

	if (m_isBullet == true) {
		//	m_box.getBody()->SetLinearVelocity(-(m_box.getBody()->GetWorld()->GetGravity()));
	}

	glm::vec3 position = glm::vec3(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, 0.0f);


	if (m_isBullet == false)
	{
		m_prefab->SetPosition(position);
		m_prefab->SetRotation(0, 0, m_rotationUpdate * 15);
	}
	else
	{
		m_bulletSprite.ModifyPos(glm::vec2(position.x, position.y), glm::vec2(2, 0.8));
	}

	if (m_rotationUpdate > 360)
		m_rotationUpdate = 0;
}

void Projectile::Render(Camera camera)
{

	if (!m_isBullet) {
		m_prefab->Update();
		m_prefab->Render(camera);
	}
	else {


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_texture.Bind(0);
		m_bulletSprite.Bind();
		m_bulletSprite.Update(m_transform, camera);
		m_bulletSprite.Render();
		glDisable(GL_BLEND);
		glUseProgram(0);

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
