#include "TimeManager.h"



TimeManager * TimeManager::m_instance = nullptr;
float TimeManager::m_deltaTime = 0.0f;
float TimeManager::m_lastFrame = 0.0f;


TimeManager::TimeManager()
{

}

TimeManager::~TimeManager()
{
}


//::.. FAKE CONSTRUCTORS ..:://
void TimeManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
		m_lastFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;
	}
}

void TimeManager::ShutDown()
{

}



void TimeManager::UpdateDeltaTime()
{
	float currentFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;
	
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}

void TimeManager::ResetDeltaTime()
{
	m_deltaTime = 0.0f;
	m_lastFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;
}

float TimeManager::GetDeltaTime()
{
	return m_deltaTime;
}

TimeManager * TimeManager::Get()
{
	return m_instance;
}
