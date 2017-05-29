#ifndef __ANIMSKELETON_H__
#define __ANIMSKELETON_H__


#include "AnimUtil.h"
#include "Transform.h"
#include "GLM\gtc\quaternion.hpp"

#include <glm.hpp>


class AnimSkeleton
{
public:
	static const uint32_t MAX_JOINTS = 30;

	//::.. CONSTRUCTORS ..:://
	AnimSkeleton();
	virtual ~AnimSkeleton();

	void Update(KeyFrame * kf, KeyFrame * preKf, float inter, bool animateBindPose = true, int32_t from = 0, int32_t to = -1);

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumJoints();
	Joint * GetJointAt(int32_t index);
	glm::mat4 * GetSkinnedTx();

	//::.. SET FUNCTIONS ..:://
	void SetSkeleton(uint32_t * parentID, glm::mat4 * localTx,
		uint32_t numJoints);
	void SetJointRotation(Transform& rotation, uint32_t jointID);

private:
	uint32_t	m_numJoints;
	Joint *		m_skel;
	glm::mat4 *	m_skinnedTx;
};


#endif // !__ANIMSKELETON_H__