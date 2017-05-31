#ifndef __ANIMUTIL_H__
#define __ANIMUTIL_H__


#include <glm.hpp>


struct KeyFrame
{
	glm::mat4 *	localTx;
};


struct Joint
{
	uint32_t	parentID;
	glm::mat4	localTx;
	glm::mat4	globalTx;
	glm::mat4	invBindPose;
};


#endif // !__ANIMUTIL_H__

