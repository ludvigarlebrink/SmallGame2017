#include "AnimSkeleton.h"

#include "TimeManager.h"

#include <iostream>
#include <iomanip>

AnimSkeleton::AnimSkeleton()
{
	m_numJoints = 0;
	m_skel = nullptr;
}


AnimSkeleton::~AnimSkeleton()
{
}

void AnimSkeleton::Update(KeyFrame * kf, KeyFrame * preKf, float inter, bool animateBindPose, int32_t from, int32_t to)
{
	if (to == -1)
	{
		to = m_numJoints - 1;
	}

	if (animateBindPose)
	{
		glm::mat4 finalMat;

		if (preKf != nullptr)
		{
			glm::quat rot1(glm::quat_cast(kf->localTx[0]));
			glm::quat rot2(glm::quat_cast(preKf->localTx[0]));
			glm::quat rot3 = glm::lerp(rot2, rot1, abs(inter));
			finalMat = glm::mat4(rot3);
			finalMat[3] = kf->localTx[0][3];
		}
		else
		{
			finalMat = kf->localTx[0];
		}

		m_skel[0].globalTx = finalMat;
		m_skinnedTx[0] = m_skel[0].globalTx * m_skel[0].invBindPose;
	}
	else
	{
		m_skel[0].globalTx = m_skel[0].localTx;
		m_skinnedTx[0] = m_skel[0].globalTx * m_skel[0].invBindPose;
	}

	for (uint32_t i = from; i <= to; i++)
	{
		glm::mat4 finalMat;

		if (preKf != nullptr)
		{
			glm::quat rot1(glm::quat_cast(kf->localTx[i]));
			glm::quat rot2(glm::quat_cast(preKf->localTx[i]));
			glm::quat rot3 = glm::lerp(rot2, rot1, inter);
			finalMat = glm::mat4(rot3);

			finalMat[3] = kf->localTx[i][3];
		}
		else
		{
			finalMat = kf->localTx[i];
		}

		m_skel[i].globalTx = m_skel[m_skel[i].parentID].globalTx * finalMat;
		m_skinnedTx[i] = m_skel[i].globalTx * m_skel[i].invBindPose;
	}
}


//::.. GET FUNCTIONS ..:://
uint32_t AnimSkeleton::GetNumJoints()
{
	return m_numJoints;
}


Joint * AnimSkeleton::GetJointAt(int32_t index)
{
	return &m_skel[index];
}


glm::mat4 * AnimSkeleton::GetSkinnedTx()
{
	return m_skinnedTx;
}


//::.. SET FUNCTIONS ..:://
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
		m_skel[i].globalTx		= m_skel[i].localTx * m_skel[m_skel[i].parentID].globalTx;
		m_skel[i].invBindPose	= glm::inverse(m_skel[i].globalTx);
	}
}

void AnimSkeleton::SetJointRotation(Transform & rotation, uint32_t jointID)
{
	rotation.SetPosition(m_skel[jointID].localTx[3].x, m_skel[jointID].localTx[3].y, m_skel[jointID].localTx[3].z);
	m_skel[jointID].globalTx = m_skel[m_skel[jointID].parentID].globalTx * rotation.GetModelMatrix();
	m_skinnedTx[jointID] = m_skel[jointID].globalTx *  m_skel[jointID].invBindPose;
}