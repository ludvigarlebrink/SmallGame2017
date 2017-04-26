#ifndef __ANIMSKELETON_H__
#define __ANIMSKELETON_H__


#include "AnimUtil.h"


#include <glm.hpp>


class AnimSkeleton
{
public:
	static const uint32_t MAX_JOINTS = 16;

	//::.. CONSTRUCTORS ..:://
	AnimSkeleton();
	virtual ~AnimSkeleton();

	void Update(KeyFrame * kf);

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumJoints();
	Joint * GetJointAt(int32_t index);
	glm::mat4 * GetSkinnedTx();

	//::.. SET FUNCTIONS ..:://
	void SetSkeleton(uint32_t * parentID, glm::mat4 * localTx,
		uint32_t numJoints);

private:
	glm::mat4 ReadHierarchy(uint32_t n, glm::mat4 kf);

private:
	uint32_t	m_numJoints;
	Joint *		m_skel;
	glm::mat4 *	m_skinnedTx;
	float		m_counter;
	
};


#endif // !__ANIMSKELETON_H__