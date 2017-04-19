#include "AnimClip.h"



AnimClip::AnimClip()
{
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
	int32_t m_curKeyI = static_cast<int32_t>(m_curKey);
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
	return &m_keys[m_curKeyI];
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


//::.. SET FUNCTIONS ..:://
void AnimClip::SetAnimation(KeyFrame * keyFrames,
	int32_t firstKey, int32_t lastKey)
{
	m_keys = keyFrames;
	m_firstKey = lastKey;
	m_numKeys = m_lastKey - m_firstKey;
}


void AnimClip::SetName(const char * name)
{
	m_name = name;
}
