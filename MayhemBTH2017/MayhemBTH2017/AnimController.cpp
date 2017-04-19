#include "AnimController.h"



AnimController::AnimController()
{
	m_clips = new AnimClip[MAX_CLIPS];
}


AnimController::~AnimController()
{
}

void AnimController::Update()
{

}

bool AnimController::SwitchAnim(const char * anim)
{


	return true;
}


bool AnimController::SwitchAnimAt(uint32_t index)
{
	m_clips[m_curClip].Stop();

	m_curClip = index;

	return false;
}


void AnimController::AddAnimation(AnimClip * clip)
{

}


//::.. SET FUNCTIONS ..:://
void AnimController::SetSkeleton(AnimSkeleton * skel)
{
	m_skel = skel;
}
