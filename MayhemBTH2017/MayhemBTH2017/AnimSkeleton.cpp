#include "AnimSkeleton.h"



AnimSkeleton::AnimSkeleton()
{
	m_numJoints = 0;
	m_skel = nullptr;
}


AnimSkeleton::~AnimSkeleton()
{
}

void AnimSkeleton::Update()
{
}

uint32_t AnimSkeleton::GetNumJoints()
{
	return m_numJoints;
}

Joint * AnimSkeleton::GetJointAt(int32_t index)
{
	return &m_skel[index];
}

void AnimSkeleton::SetSkeleton(uint32_t * parentID, glm::mat4 * localTx, 
	uint32_t numJoints)
{
	m_numJoints = numJoints;

	m_skel = new Joint[m_numJoints];
	m_skinnedTx = new glm::mat4[m_numJoints];

	for (uint32_t i = 0; i < m_numJoints; i++)
	{
		m_skel[i].localTx	= localTx[i];
		m_skel[i].parentID	= parentID[i];
	}

	// Set up the root.
	m_skel[0].parentID		= 0;
	m_skel[0].globalTx		= m_skel[0].localTx;
	m_skel[0].invBindPose	= glm::inverse(m_skel[0].globalTx);

	for (uint32_t i = 1; i < m_numJoints; i++)
	{
		Joint &j		= m_skel[i];
		j.globalTx		= m_skel[j.parentID].globalTx * j.localTx;
		j.invBindPose	= glm::inverse(j.globalTx);
	}
}

void AnimSkeleton::Update(KeyFrame * kf)
{
	m_skel[0].parentID	= m_skel[0].parentID;
	m_skinnedTx[0]		= m_skel[0].globalTx * m_skel[0].invBindPose;

	for (uint32_t i = 1; i < m_numJoints; i++)
	{
		Joint &j		= m_skel[i];
		j.globalTx		= m_skel[j.parentID].globalTx * kf->localTx[i];
		m_skinnedTx[i]	= j.globalTx * j.invBindPose;
	}
}
