#ifndef __ANIMCONTROLLER_H__
#define __ANIMCONTROLLER_H__


#include "AnimClip.h"


class AnimController
{
public:
	AnimController();
	virtual ~AnimController();

	void Update();

	void AddAnimation(AnimClip * animation);

private:
};


#endif