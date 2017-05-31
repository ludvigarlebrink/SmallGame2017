#include "Skull.h"



Skull::Skull()
{
	m_skullFilter.categoryBits = SKULL;
	m_skullFilter.maskBits = BOUNDARY | PLAYER1 | PLAYER2 | PLAYER3 | PLAYER4;
	

}


Skull::~Skull()
{
	for (int i = 0; i < m_skull.size(); i++)
	{
		m_skull.at(i)->skullPrefab->Free();
		m_skull.at(i)->skullPrefab = nullptr;
	}
}

//void Skull::Update(Player & player)
//{
//
//	m_dead = player.GetDead();
//
//	if(!m_dead)
//		m_skullTimer = 0;
//
//	if (m_dead)
//		m_skullTimer++;
//
//	if (m_dead && m_skullTimer == 1)
//	{
//		skullStruct * tempStruct = new skullStruct;
//
//		m_deathPos = player.GetBox().getBody()->GetPosition();
//
//		Prefab * m_tempSkull = PrefabManager::Instantiate("lukas", nullptr, nullptr, 0, "Candle");
//		m_tempSkull->Create();
//		m_tempSkull->SetScale(glm::vec3(1, 1, 1));
//		m_tempSkull->Rotate(0, 90, 0);
//
//		Box m_tempBoxSkull;
//		m_tempBoxSkull.InitDynamic(player.GetWorld(), glm::vec2(m_deathPos.x, m_deathPos.y), glm::vec2(1.5, 1.5));
//
//		m_tempBoxSkull.getBody()->SetTransform(m_deathPos, 0);
//		m_tempSkull->SetPosition(m_tempBoxSkull.getBody()->GetPosition().x, m_tempBoxSkull.getBody()->GetPosition().y, 0);
//
//		m_tempBoxSkull.getFixture()->SetFriction(1.0);
//		m_tempBoxSkull.getFixture()->SetRestitution(0.0);
//		m_tempBoxSkull.getBody()->SetLinearDamping(0.0);
//		m_tempBoxSkull.getBody()->ResetMassData();
//
//		m_tempBoxSkull.getFixture()->SetFilterData(m_skullFilter);
//		m_tempBoxSkull.getBody()->SetUserData(tempStruct);
//
//		tempStruct->skullBox = m_tempBoxSkull;
//		tempStruct->skullPrefab = m_tempSkull;
//		tempStruct->skullID = m_skullID;
//		m_skullID++;
//
//		m_skull.push_back(tempStruct);
//
//		glm::vec2 scale = glm::vec2(1.5);
//
//		m_yolo.SetPosition(m_deathPos.x, m_deathPos.y);
//		m_yolo.SetSize(50, 50);
//
//	}
//}

void Skull::Render(Camera & camera)
{
	for (int i = 0; i < m_skull.size(); i++)
	{
		m_skull[i]->skullPrefab->Render(camera);
		m_yolo.Render();
	}
}

void Skull::SetCollision(bool player)
{
	m_collidedPlayer = player;
}
