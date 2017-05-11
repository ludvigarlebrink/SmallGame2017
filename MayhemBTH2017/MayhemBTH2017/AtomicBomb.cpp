#include "AtomicBomb.h"



AtomicBomb::AtomicBomb()
{
	m_bomber = PrefabManager::Instantiate("Candle", nullptr, nullptr, 0, "Candle");
	m_atomicBomb = PrefabManager::Instantiate("Candle", nullptr, nullptr, 0, "Candle");

//	VideoManager->VM

	m_bomber->SetPosition(glm::vec3(1, 0.0f, -10.0f));
}


AtomicBomb::~AtomicBomb()
{
}


void AtomicBomb::StartBombSequence()
{

}


void AtomicBomb::Update(Camera &cam)
{
	m_bomber->Render(cam);
}
