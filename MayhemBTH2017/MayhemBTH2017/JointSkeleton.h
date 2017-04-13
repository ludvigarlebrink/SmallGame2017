#ifndef __JOINTSKELETON_H__
#define __JOINTSKELETON_H__


#include "Joint.h"


#include <vector>
#include <glm.hpp>

class JointSkeleton
{
public:
	JointSkeleton();
	virtual ~JointSkeleton();

	void AddJoint(Joint joint);
	void AddMatTemp(glm::mat4 hej1, glm::mat4 hej2, glm::mat4 hej3, glm::mat4 hej4);
	glm::mat4* GetMat();

private:
	std::vector<Joint>	m_joints;
	std::vector<glm::mat4> matTemp;
};


#endif // !__JOINTSKELETON_H__