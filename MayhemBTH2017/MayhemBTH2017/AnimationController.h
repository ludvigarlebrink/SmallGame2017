#ifndef __ANIMATIONCONTROLLER_H__
#define __ANIMATIONCONTROLLER_H__


#include "Mesh.h"
#include "JointSkeleton.h"
#include "AnimationClip.h"


#include <vector>
#include <cstdlib>


class AnimationController
{
public:
	AnimationController();
	virtual ~AnimationController();

	void PlayAnimation(uint32_t animation);

	uint32_t GetNrOfAnimations();
	uint32_t GetCurrentPlayingAnimation();

private:
	Mesh						m_mesh;
	JointSkeleton				m_bindPose;
	std::vector<AnimationClip>	m_animations;
	uint32_t					m_currentAnimation;
	


};


#endif // __ANIMATIONCONTROLLER_H__