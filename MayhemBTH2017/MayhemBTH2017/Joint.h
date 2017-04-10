#ifndef __JOINT_H__
#define __JOINT_H__


#include <cstdint>


class Joint
{
public:
	Joint();
	virtual ~Joint();

private:
	uint32_t	m_parentID;
};


#endif // __JOINT_H__