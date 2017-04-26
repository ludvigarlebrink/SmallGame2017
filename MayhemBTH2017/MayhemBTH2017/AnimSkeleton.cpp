#include "AnimSkeleton.h"


#include <iostream>
#include <iomanip>
#include "TimeManager.h"

AnimSkeleton::AnimSkeleton()
{
	m_numJoints = 0;
	m_skel = nullptr;
	m_counter = 0.0f;
}


AnimSkeleton::~AnimSkeleton()
{
}

void AnimSkeleton::Update(KeyFrame * kf)
{
	m_skel[0].globalTx = m_skel[0].localTx;
	m_skinnedTx[0] = m_skel[0].invBindPose * m_skel[0].globalTx;
	
	m_counter += TimeManager::Get()->GetDeltaTime();

	for (uint32_t i = 1; i < m_numJoints; i++)
	{
		m_skel[i].globalTx = kf->localTx[i] * m_skel[m_skel[i].parentID].globalTx;
		m_skinnedTx[i] = m_skel[i].invBindPose * m_skel[i].globalTx;
	//
	//
	//	for (int j = 0; j < 4; j++)
	//	{
	//		for (int n = 0; n < 4; n++)
	//		{
	//
	//			std::cout << std::fixed << std::setprecision(4) << kf->localTx[i][j][n] << "\t\t";
	//		}
	//
	//		std::cout << std::endl;
	//	}
		// REMOVE
	//	getchar();
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

glm::mat4 AnimSkeleton::ReadHierarchy(uint32_t n, glm::mat4 kf)
{
	if (m_skel[n].parentID == 0)
	{
		m_skel[0].globalTx = m_skel[0].localTx;
		return m_skel[0].globalTx * m_skel[0].invBindPose;
	}
	
	m_skel[n].globalTx = m_skel[m_skel[n].parentID].globalTx * kf;
	glm::mat4 global = m_skel[n].globalTx * m_skel[n].invBindPose;
	return global * ReadHierarchy(m_skel[n].parentID, kf);
}
