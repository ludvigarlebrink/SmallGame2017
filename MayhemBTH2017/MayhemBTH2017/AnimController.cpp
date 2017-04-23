#include "AnimController.h"



AnimController::AnimController()
{
//	m_clips = new AnimClip[MAX_CLIPS];
}


AnimController::~AnimController()
{
}

void AnimController::Update(GLuint locations)
{
	m_clips[m_currClip]->Update();
	m_skel->Update(m_clips[m_currClip]->GetCurrentKeyFrame());

	glUniformMatrix4fv(locations, m_skel->GetNumJoints(), GL_FALSE, &m_skel->GetSkinnedTx()[0][0][0]);
}

bool AnimController::SwitchAnim(const char * anim)
{


	return true;
}


bool AnimController::SwitchAnimAt(uint32_t index)
{
	m_clips[m_currClip]->Stop();

	m_currClip = index;

	return false;
}


void AnimController::AddAnimation(AnimClip * clip)
{
	m_clips.push_back(clip);
}


//::.. SET FUNCTIONS ..:://
void AnimController::SetSkeleton(AnimSkeleton * skel)
{
	m_skel = skel;
}
