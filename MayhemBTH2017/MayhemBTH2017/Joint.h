#ifndef __JOINT_H__
#define __JOINT_H__


#include "glm.hpp"


#include <cstdint>


class Joint
{
public:
	Joint();
	virtual ~Joint();

	uint32_t GetParentID();

	void SetParentID(uint32_t parentID);

private:
	uint32_t	m_parentID;
	glm::mat4	m_transform;
	bool		m_isKeyFramed;
};


#endif // __JOINT_H__