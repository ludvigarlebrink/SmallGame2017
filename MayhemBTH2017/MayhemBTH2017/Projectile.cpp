#include "Projectile.h"



Projectile::Projectile()
{

	//m_texture
	m_trailTime = 0.0f;
	m_time = 0.0;
	m_rotationUpdate = 0.0f;
	m_renderParticles = false;
	m_hasParticles = false;
	m_particleTimer = 0;

	//m_texture = m_textureHandler.Import(".\\Assets\\Textures\\fireball.png");
}


Projectile::~Projectile()
{
}

void Projectile::InitProjectile(b2World * world, glm::vec2 pos, glm::vec2 scale, float restitution, float friction, float damping, float density, float fireRate, bool startUp, Prefab * prefab, int controllerID, float life)
{
	m_collisionSoundPath = "explosion1";
	m_soundManager = SoundManager::Get();
	m_hasParticles = false;

	m_trailParticles = nullptr;

	m_renderSmoke = false;
	m_isBullet = false;

	m_collision = false;

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

	m_restitution = restitution;

	m_box.getFixture()->SetFriction(friction);
	m_box.getFixture()->SetDensity(density);
	m_box.getBody()->SetLinearDamping(damping);
	m_box.getFixture()->SetFilterData(filter);
	m_box.getBody()->ResetMassData();

}

void Projectile::SetTexture(Texture texture)
{

	m_texture = texture;


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

void Projectile::SetHasParticles(bool has)
{
	m_hasParticles = has;
}

void Projectile::SetActive(bool active)
{
	m_active = active;
}


void Projectile::InitParticles(std::string shadername, glm::vec4 col, GLfloat size, const int nrof, float life) {

	m_shadername = shadername;
	m_col = col;
	m_size = size;
	m_nrof = nrof;
	m_particleLife = life;


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
	return m_collision;
}

void Projectile::CollisionTimer()
{
	m_collisionTimer += TimeManager::GetDeltaTime();

	if (m_collisionTimer >= 0.3f) {
		m_collision = false;
	}
}

void Projectile::CollisionTrue()
{
	m_collisionTimer = 0.0f;
	m_collision = true;
}

void Projectile::SetCollisionSound(const char * filepath)
{
	m_collisionSoundPath = filepath;
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


	m_trailTime += TimeManager::GetDeltaTime();

	CollisionTimer();

	m_lifeTime += TimeManager::GetDeltaTime();


	//WHEN PROJECTILE CONTACT WITH GROUND
	if (m_contact)
	{
		/*if (m_lifeTime >= m_life)
		{*/
		GetBox().getBody()->SetActive(false);
		SetActive(false);
		m_soundManager->PlaySFX(m_collisionSoundPath);


		glm::vec3 position = glm::vec3(m_box.getBody()->GetPosition().x / 2, m_box.getBody()->GetPosition().y / 2, 0.0f);

		if (m_hasParticles) {
			m_emitter.SetParticleSystem(m_shadername, position, m_col, m_size, m_nrof, m_particleLife);
			m_renderParticles = true;
		}


		m_lifeTime = 0;
		//}
	}

	if (m_active)
	{

		glm::vec3 position = glm::vec3(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, 0.0f);
		m_prefabPointer.SetPosition(position);
		m_rotationUpdate += 10;
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

	if (m_hasParticles && m_renderParticles) {


		Transform transform;

		transform.SetPosition(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, 0);

		m_texture.Bind(0);
		//	glActiveTexture(0);

		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_texture.Bind(m_texture.GetTexture());


		m_emitter.Update();
		m_emitter.Render(transform);

		glDepthMask(true);
		glDisable(GL_BLEND);
	
	}
}

void Projectile::RenderShadow(Camera camera)
{
	if (m_active)
	{
		m_prefabPointer.Update();
		m_prefabPointer.RenderShadow(camera);
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

