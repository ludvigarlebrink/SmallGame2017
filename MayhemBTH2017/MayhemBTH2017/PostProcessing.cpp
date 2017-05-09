#include "PostProcessing.h"

PostProcessing * PostProcessing::m_instance = nullptr;

float PostProcessing::m_currentFrame = 0.0f;
float PostProcessing::m_deltaTime = 0.0f;
float PostProcessing::m_lastFrame = 0.0f;
float PostProcessing::m_shakeTime = 0.0f;

bool PostProcessing::m_shake = false;
bool PostProcessing::m_chaos = false;

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

bool PostProcessing::IsShaking()
{
	return m_shake;
}

bool PostProcessing::IsChaos()
{
	return m_chaos;
}


void PostProcessing::StartTimer()
{
	m_deltaTime = 0.0;
	m_lastFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;

	m_currentFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f;

	m_deltaTime = m_currentFrame - m_lastFrame;
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
	case NOTHING:
		m_shake = false;
		m_chaos = false;
		break;
	case SHAKE:
		m_shake = true;
		break;
	case CHAOS:
		m_chaos = true;
		break;
	case CHAOS | SHAKE:
		m_shake = true;
		m_chaos = true;
		break;
	}

}

PostProcessing * PostProcessing::Get()
{
	return m_instance;
}
