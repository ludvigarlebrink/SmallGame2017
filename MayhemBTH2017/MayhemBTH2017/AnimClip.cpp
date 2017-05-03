#include "AnimClip.h"



AnimClip::AnimClip()
{
	m_timeManager = TimeManager::Get();
	m_speedModifier = 1.0f;
}


AnimClip::~AnimClip()
{
}


void AnimClip::Play()
{
	m_isPlaying = true;
}


void AnimClip::Stop()
{
	m_isPlaying = false;
}


void AnimClip::Update()
{
	m_inter += m_timeManager->GetDeltaTime() * 24.0f * m_speedModifier;

	if (m_inter > 1.000f)
	{
		m_inter -= static_cast<int>(m_inter);
		m_preKeyI = m_currKeyI;
		++m_currKeyI;
		if (m_currKeyI > 29)
		{
			m_currKeyI = 0;
		}
	}
	else if (m_inter < -1.000f)
	{
		m_inter -= static_cast<int>(m_inter);
		m_preKeyI = m_currKeyI;
		--m_currKeyI;
		if (m_currKeyI < 0)
		{
			m_currKeyI = 28;
		}
	}
}


//::.. GET FUNCTIONS ..:://
const char * AnimClip::GetName() const
{
	return m_name;
}


bool AnimClip::GetIsPlaying() const
{
	return m_isPlaying;
}


KeyFrame * AnimClip::GetCurrentKeyFrame() const
{
	return &m_keys[m_currKeyI];
}


KeyFrame * AnimClip::GetPreviousKeyFrame() const
{
	return &m_keys[m_preKeyI];
}


uint32_t AnimClip::GetNumKeys()
{
	return m_numKeys;
}


int32_t AnimClip::GetFirstKey()
{
	return m_firstKey;
}


int32_t AnimClip::GetLastKey()
{
	return m_lastKey;
}

float AnimClip::GetInter() const
{
	return abs(m_inter);
}


//::.. SET FUNCTIONS ..:://
void AnimClip::SetAnimation(KeyFrame * keyFrames,
	int32_t firstKey, int32_t lastKey)
{
	m_inter = 0;
	m_currKeyI = 0;
	m_preKeyI = 28;
	m_keys = keyFrames;
	m_firstKey = lastKey;
	m_numKeys = m_lastKey - m_firstKey;
}


void AnimClip::SetName(const char * name)
{
	m_name = name;
}

void AnimClip::SetSpeedModifier(float speed)
{
	m_speedModifier = speed;
}
