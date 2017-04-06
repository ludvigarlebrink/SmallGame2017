#include "TimeManager.h"

#include <iostream>

TimeManager * TimeManager::m_instance = nullptr;


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

float TimeManager::GetDeltaTime()
{
	return m_deltaTime;
}

TimeManager * TimeManager::Get()
{
	return m_instance;
}
