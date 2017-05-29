#include "AnimController.h"
#include "InputManager.h"

#include "MrAnimHandler.h"

#include "GLM\gtc\quaternion.hpp"

AnimController::AnimController()
{

}


AnimController::~AnimController()
{
	Free();
}


void AnimController::Free()
{
	m_clips.clear();
	delete m_skel;
}


void AnimController::QuickUpdate(GLuint locations)
{
	glUniformMatrix4fv(locations, m_skel->GetNumJoints(), GL_FALSE, &m_skel->GetSkinnedTx()[0][0][0]);
}

void AnimController::Update(GLuint locations)
{
	m_clips[m_currClip]->Update();

	m_skel->Update(m_clips[m_currClip]->GetCurrentKeyFrame(), 
		m_clips[m_currClip]->GetPreviousKeyFrame(), m_clips[m_currClip]->GetInter(), false, 12);

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


//::.. GET FUNCTIONS ..:://
AnimSkeleton * AnimController::GetSkeleton() const
{
	return m_skel;
}


uint32_t AnimController::GetNumClips() const
{
	return m_clips.size();
}


uint32_t AnimController::GetCurrentClip() const
{
	return m_currClip;
}


AnimClip * AnimController::GetCurrentAnimClip() const
{
	return m_clips[m_currClip];
}


std::vector<AnimClip*> AnimController::GetClips() const
{
	return m_clips;
}


//::.. SET FUNCTIONS ..:://
void AnimController::SetSkeleton(AnimSkeleton * skel)
{
	m_skel = skel;

	MrAnimHandler * animHandler = new MrAnimHandler;

	animHandler->Import(".\\Assets\\Animations\\Player@Up.mranim");

	m_keyUp = new KeyFrame[animHandler->GetNumKeyFramedJoints()];
	m_keyUp->localTx = new glm::mat4[m_skel->GetNumJoints()];

	for (uint32_t j = 0; j < m_skel->GetNumJoints(); j++)
	{
		m_keyUp->localTx[j] = animHandler->GetKeyFramedJoints()[j].matrix[0];
	}

	animHandler->Import(".\\Assets\\Animations\\Player@Run.mranim");

	m_keyBase = new KeyFrame[animHandler->GetNumKeyFramedJoints()];
	m_keyBase->localTx = new glm::mat4[m_skel->GetNumJoints()];

	for (uint32_t j = 0; j < m_skel->GetNumJoints(); j++)
	{
		m_keyBase->localTx[j] = animHandler->GetKeyFramedJoints()[j].matrix[0];
	}

	animHandler->Import(".\\Assets\\Animations\\Player@Down_01.mranim");

	m_keyDown = new KeyFrame[animHandler->GetNumKeyFramedJoints()];
	m_keyDown->localTx = new glm::mat4[m_skel->GetNumJoints()];

	for (uint32_t j = 0; j < m_skel->GetNumJoints(); j++)
	{
		m_keyDown->localTx[j] = animHandler->GetKeyFramedJoints()[j].matrix[0];
	}

	animHandler->Import(".\\Assets\\Animations\\Player@Down_02.mranim");

	m_keyDown2 = new KeyFrame[animHandler->GetNumKeyFramedJoints()];
	m_keyDown2->localTx = new glm::mat4[m_skel->GetNumJoints()];

	for (uint32_t j = 0; j < m_skel->GetNumJoints(); j++)
	{
		m_keyDown2->localTx[j] = animHandler->GetKeyFramedJoints()[j].matrix[0];
	}

	delete animHandler;
}