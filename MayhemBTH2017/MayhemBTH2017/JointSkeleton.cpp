#include "JointSkeleton.h"



JointSkeleton::JointSkeleton()
{
	Joint world;
	m_joints.push_back(world);
}


JointSkeleton::~JointSkeleton()
{
}

void JointSkeleton::AddJoint(Joint joint)
{
	m_joints.push_back(joint);
}