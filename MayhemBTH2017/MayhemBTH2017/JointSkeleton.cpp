#include "JointSkeleton.h"



JointSkeleton::JointSkeleton()
{
}


JointSkeleton::~JointSkeleton()
{
}

void JointSkeleton::AddJoint(Joint joint)
{
	m_joints.push_back(joint);
}

void JointSkeleton::AddMatTemp(glm::mat4 hej)
{
	matTemp.push_back(hej);
}

glm::mat4* JointSkeleton::GetMat()
{

	glm::mat4 hej[4];
	glm::mat4 hej2(1.0f);


	hej[0] = glm::transpose(hej2 * matTemp[0]);
	hej[1] = glm::transpose(hej2 * matTemp[1]);
	hej[2] = glm::transpose(hej2 * matTemp[2]);
	hej[3] = glm::transpose(hej2 * matTemp[3]);


	return hej;
}

