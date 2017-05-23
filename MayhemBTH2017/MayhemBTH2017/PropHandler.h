#ifndef __PROPHANDLER_H__
#define __PROPHANDLER_H__


#include "PrefabManager.h"
#include "Transform.h"


#include <cstring>
#include <glm.hpp>


class PropHandler
{
public:
	static const uint32_t NUM_PROPS = 16;

	struct PropInfo
	{
		const char *	name;
		bool			hasAnimation;
		uint32_t		gridX;
		uint32_t		gridY;
		float			rotY;
	};

	struct Prop
	{
		uint32_t	id;
		Prefab *	prefab;
	};

	PropHandler();
	virtual ~PropHandler();

	Prop * Instantiate(const char * name);
	Prop * Instantiate(uint32_t id);

	PropInfo * GetPropInfo(uint32_t id);

private:
	void Init();

private:
	PropHandler *	m_instance;

	PropInfo *		m_props[NUM_PROPS];
};


#endif