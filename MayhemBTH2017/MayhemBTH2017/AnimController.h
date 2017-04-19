#ifndef __ANIMCONTROLLER_H__
#define __ANIMCONTROLLER_H__


#include "AnimClip.h"
#include "AnimSkeleton.h"


class AnimController
{
public:
	static const uint32_t MAX_CLIPS = 10;

	AnimController();
	virtual ~AnimController();

	void Update();

	bool SwitchAnim(const char * anim);
	bool SwitchAnimAt(uint32_t index);

	void AddAnimation(AnimClip * clip);

	//::.. SET FUNCTIONS ..:://
	void SetSkeleton(AnimSkeleton * skel);

private:
	uint32_t	m_numClips;
	uint32_t	m_curClip;
	AnimClip *	m_clips;

	AnimSkeleton * m_skel;


};


#endif