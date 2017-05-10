#include "PostProcessingManager.h"

PostProcessingManager * PostProcessingManager::m_instance = nullptr;

float PostProcessingManager::m_currentFrame = 0.0f;
float PostProcessingManager::m_deltaTime = 0.0f;
float PostProcessingManager::m_lastFrame = 0.0f;
float PostProcessingManager::m_shakeTime = 0.0f;
float PostProcessingManager::m_chaosTime = 0.0f;

bool PostProcessingManager::m_shake = false;
bool PostProcessingManager::m_chaos = false;

PostProcessingManager::PostProcessingManager()
{
}


PostProcessingManager::~PostProcessingManager()
{
}

void PostProcessingManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
	}
}

void PostProcessingManager::ShutDown()
{
}

bool PostProcessingManager::IsShaking()
{
	return m_shake;
}

bool PostProcessingManager::IsChaos()
{
	return m_chaos;
}

float PostProcessingManager::GetShakingTime()
{
	return m_shakeTime;
}
float PostProcessingManager::GetChaosTime()
{
	return m_chaosTime;
}


void PostProcessingManager::StartTimer()
{
		
	//m_lastFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;

	m_currentFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;

	m_deltaTime = m_currentFrame - m_lastFrame;
	m_lastFrame = m_currentFrame;
	//std::cout << m_deltaTime << std::endl;
}

void PostProcessingManager::Shake()
{

}

void PostProcessingManager::Update(int state)
{
	StartTimer();
	switch (state)
	{
	default:
		break;
	case NOTHING:
		/*m_shake = false;
		m_chaos = false;*/
		break;
	case SHAKE:
		m_shake = true;
		m_shakeTime = 0.15f;
		break;
	case CHAOS:
		m_chaos = true;
		m_chaosTime = 3.0f;
		break;
	case CHAOS | SHAKE:
		m_shake = true;
		//m_chaos = true;
		break;
	}
	if (m_chaosTime > 0.0f)
	{

		m_chaosTime -= m_deltaTime;
		if (m_chaosTime <= 0.0)
		{
			m_chaos = false;
		}
	}

	if (m_shakeTime > 0.0f)
	{

		m_shakeTime -= m_deltaTime;
		if (m_shakeTime <= 0.0)
		{
			m_shake = false;
			m_chaos = false;
		}
	}
	//std::cout << "T\t" << m_shakeTime << std::endl;

}

PostProcessingManager * PostProcessingManager::Get()
{
	return m_instance;
}
