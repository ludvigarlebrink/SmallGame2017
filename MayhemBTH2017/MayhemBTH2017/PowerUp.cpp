#include "PowerUp.h"



PowerUp::PowerUp()
{

}

PowerUp::~PowerUp()
{
	Free();
}

void PowerUp::Create(b2World* world, glm::vec2 pos)
{

	m_powerupPrefab = PrefabManager::Instantiate("Candle", nullptr, nullptr, 0, "Candle");

	m_powerupPrefab->Create();
	m_powerupPrefab->SetScale(glm::vec3(1.5, 1.5, 1.5));
	m_powerupPrefab->Rotate(glm::vec3(0.0, 90.0, 0.0));
	scale = glm::vec2(1.5);

	m_boundingBox.InitDynamic(world, pos, scale);
	SetActive(false);

	//m_sprite.CreateSprite(glm::vec2(GetBox().getBody()->GetPosition().x - (scale.x / 2), GetBox().getBody()->GetPosition().y - (scale.y / 2)), glm::vec2(scale.x, scale.y));
	//m_sprite.Init(".\\Assets\\GLSL\\ColliderShader", 0, 0);

	m_filter.categoryBits = POWERUP;
	m_filter.maskBits = BOUNDARY | PLAYER1 | PLAYER2 | PLAYER3 | PLAYER4;
	m_boundingBox.getFixture()->SetFilterData(m_filter);

	m_boundingBox.getBody()->SetUserData(this);

	lifeTime = 0;
	deathBound = 10.0;
}

void PowerUp::CreateSkull(b2World * world, glm::vec2 pos)
{
	m_powerupPrefab = PrefabManager::Instantiate("lukas", nullptr, nullptr, 0, "Candle");

	m_powerupPrefab->Create();
	m_powerupPrefab->SetScale(glm::vec3(1.5, 1.5, 1.5));
	m_powerupPrefab->Rotate(glm::vec3(0.0, 90.0, 0.0));
	scale = glm::vec2(1.5);

	m_boundingBox.InitDynamic(world, pos, scale);
	SetActive(false);

	m_filter.categoryBits = SKULL;
	m_filter.maskBits = BOUNDARY | PLAYER1 | PLAYER2 | PLAYER3 | PLAYER4;
	m_boundingBox.getFixture()->SetFilterData(m_filter);

	m_boundingBox.getBody()->SetUserData(this);

	lifeTime = 0;
	deathBound = 5.0;
	m_score = 0;
}

//::.. RENDER ..:://
void PowerUp::Render(Camera camera) {

	//Transform transform;
	//m_sprite.Bind();
	//m_sprite.Update(transform, camera);
	//m_sprite.Render();
	m_powerupPrefab->Render(camera);

}

Box PowerUp::GetBox()
{
	return m_boundingBox;
}

//Prefab* PowerUp::GetPrefab()
//{
//	return m_powerupPrefab;
//}

bool PowerUp::GetActive()
{
	return m_active;
}

void PowerUp::CollidedWithPlayer(bool player)
{
	if (player)
	{
		m_collidedPlayer = true;
		return;
	}

	m_collidedPlayer = false;
}

uint32_t PowerUp::GetScore()
{
	return m_score;
}

b2Filter PowerUp::GetFilter()
{
	return m_filter;
}

void PowerUp::SetActive(bool active)
{
	m_active = active;
	m_boundingBox.getBody()->SetActive(active);
	m_boundingBox.getBody()->SetAwake(active);
}

void PowerUp::RandPosition()
{
	srand(time(NULL));
	b2Vec2 r;
	r.x = rand() % 80 + 2;
	r.y = rand() % 44 + 2;

	m_boundingBox.getBody()->SetTransform(r, 0);

}

void PowerUp::SetPosition(b2Vec2 value)
{
	m_boundingBox.getBody()->SetTransform(value, 0);
}

void PowerUp::SetScore(uint32_t value)
{
	m_score = value;
}



void PowerUp::Update()
{
	lifeTime += TimeManager::Get()->GetDeltaTime();

	if (m_collidedPlayer)
	{
		m_collidedPlayer = false;
		SetActive(false);
	}

	GLfloat xPos = m_boundingBox.getBody()->GetPosition().x;
	GLfloat yPos = m_boundingBox.getBody()->GetPosition().y;
	GLfloat xScale = m_boundingBox.getScale().x;
	GLfloat yScale = m_boundingBox.getScale().y;

	m_powerupPrefab->SetPosition(glm::vec3(xPos, yPos, 0));

	if (lifeTime > deathBound)
	{
		SetActive(false);
		lifeTime = 0;
	}
}

void PowerUp::SkullUpdate()
{
	lifeTime += TimeManager::Get()->GetDeltaTime();

	if (m_collidedPlayer)
	{
		m_collidedPlayer = false;
		SetActive(false);
	}

	GLfloat xPos = m_boundingBox.getBody()->GetPosition().x;
	GLfloat yPos = m_boundingBox.getBody()->GetPosition().y;
	GLfloat xScale = m_boundingBox.getScale().x;
	GLfloat yScale = m_boundingBox.getScale().y;

	m_powerupPrefab->SetPosition(glm::vec3(xPos, yPos, 0));

	if (lifeTime > deathBound)
	{
		SetActive(false);
		lifeTime = 0;
	}
}

void PowerUp::Free()
{
	m_boundingBox.DestroyBody();

	delete m_powerupPrefab;
}
