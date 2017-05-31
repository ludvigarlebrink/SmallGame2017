#include "PostProcessingManager.h"

PostProcessingManager * PostProcessingManager::m_instance = nullptr;

float PostProcessingManager::m_currentFrame = 0.0f;
float PostProcessingManager::m_deltaTime = 0.0f;
float PostProcessingManager::m_lastFrame = 0.0f;
float PostProcessingManager::m_shakeTime = 0.0f;
float PostProcessingManager::m_chaosTime = 0.0f;
float PostProcessingManager::m_atomicTime = 0.0f;

bool PostProcessingManager::m_shake = false;
bool PostProcessingManager::m_chaos = false;
bool PostProcessingManager::m_atomic = false;

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

bool PostProcessingManager::IsAtomic()
{
	return m_atomic;
}

float PostProcessingManager::GetShakingTime()
{
	return m_shakeTime;
}
float PostProcessingManager::GetChaosTime()
{
	return m_chaosTime;
}

float PostProcessingManager::GetAtmoicTime()
{
	return m_atomicTime;
}


void PostProcessingManager::Shake()
{

}


void PostProcessingManager::Update()
{
	if (!m_chaos && !m_shake && !m_atomic)
	{
		return;
	}

	if (m_chaosTime > 0.0f)
	{

		m_chaosTime -= TimeManager::GetDeltaTime();
		if (m_chaosTime <= 0.0)
		{
			m_chaos = false;
		}
	}

	if (m_shakeTime > 0.0f)
	{

		m_shakeTime -= TimeManager::GetDeltaTime();
		if (m_shakeTime <= 0.0)
		{
			m_shake = false;
			m_chaos = false;
		}
	}
	if (m_atomicTime > 0.0f)
	{

		m_atomicTime -= TimeManager::GetDeltaTime() * 4;
		if (m_atomicTime <= 0.0)
		{
			m_shake = false;
			m_chaos = false;
			m_atomic = false;
		}
	}
}


void PostProcessingManager::SetState(int state)
{
	switch (state)
	{
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
	case ATOMIC:
		m_atomic = true;
		m_atomicTime = 20;
	case CHAOS | SHAKE:
		m_shake = true;
		//m_chaos = true;
		break;
	default:
		break;
	}
}


PostProcessingManager * PostProcessingManager::Get()
{
	return m_instance;
}
