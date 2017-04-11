#ifndef __JOINT_H__
#define __JOINT_H__


#include "glm.hpp"


#include <cstdint>
#include <string>

class Joint
{
public:
	Joint();
	virtual ~Joint();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetParentID();
	glm::mat4 GetTransform();

	//::.. SET FUNCTIONS ..:://
	void SetParentID(uint32_t parentID);
	void SetTransform(glm::mat4 transform);


private:
	std::string m_name;
	uint32_t	m_parentID;
	glm::mat4	m_NodeTransform;
	glm::mat4	m_offsetMatrix;
	glm::mat4	m_finalTransformation;

};


#endif // __JOINT_H__