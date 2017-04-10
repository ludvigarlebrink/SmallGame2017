#ifndef __ANIMATION_H__
#define __ANIMATION_H__


#include "KeyFrame.h"


#include <vector>
#include <cstdint>


class Animation
{
public:
	Animation();
	virtual ~Animation();

	//::.. MODIFY FUNCTIONS ..:://
	void Play();
	void Stop();

	void LoadKeyFrames();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNrOfKeyFrames();


private:
	float					m_timer;
	std::vector<KeyFrame>	m_keyFrames;
};


#endif // __ANIMATION_H__