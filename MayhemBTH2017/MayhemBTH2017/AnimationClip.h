#ifndef __ANIMATIONCLIP_H__
#define __ANIMATIONCLIP_H__


#include "KeyFrame.h"


#include <vector>
#include <cstdint>


class AnimationClip
{
public:
	AnimationClip();
	virtual ~AnimationClip();

	//::.. MODIFY FUNCTIONS ..:://
	void Play();
	void Stop();

	void LoadKeyFrames();

	//::.. GET FUNCTIONS ..:://
	bool GetIsPlaying();
	uint32_t GetNrOfKeyFrames();


private:
	bool					m_isPlaying;
	bool					m_isRepeating;
	float					m_timer;
	std::vector<KeyFrame>	m_keyFrames;
};


#endif // __ANIMATION_H__