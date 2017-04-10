#ifndef __JOINTSKELETON_H__
#define __JOINTSKELETON_H__


#include "Joint.h"


#include <vector>


class JointSkeleton
{
public:
	JointSkeleton();
	virtual ~JointSkeleton();

	void AddJoint(Joint joint);

private:
	std::vector<Joint>	m_joints;
};


#endif // __JOINTSKELETON_H__