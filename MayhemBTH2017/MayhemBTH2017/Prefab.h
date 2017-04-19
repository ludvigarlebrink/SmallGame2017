#ifndef __PREFAB_H__
#define __PREFAB_H__


#include "Transform.h"


class Prefab
{
public:
	Prefab();
	virtual ~Prefab();

	const char * GetName();

private:
	Transform m_transform;
};


#endif 