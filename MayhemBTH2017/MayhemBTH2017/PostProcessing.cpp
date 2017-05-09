#include "PostProcessing.h"

PostProcessing * PostProcessing::m_instance = nullptr;

PostProcessing::PostProcessing()
{
}


PostProcessing::~PostProcessing()
{
}

void PostProcessing::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
	}
}

void PostProcessing::ShutDown()
{
}

bool* PostProcessing::GetBools()
{
	return m_bools;
}

void PostProcessing::StartTimer()
{
	m_deltaTime = 0.0;
	m_lastFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;

	currentFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;

	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;
}

void PostProcessing::Shake()
{
	m_shakeTime = 0.05f;

}

void PostProcessing::Update(int state)
{
	switch (state)
	{
	default:
		break;
	case 0:
		m_shake = false;
		m_chaos = false;
		break;
	case 1:
		m_shake = true;
		break;
	case 2:
		m_chaos = true;

	}

}

PostProcessing * PostProcessing::Get()
{
	return m_instance;
}
