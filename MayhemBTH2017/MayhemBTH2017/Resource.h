#ifndef __RESOURCE_H__
#define __RESOURCE_H__


#include "Level.h"
#include "Mesh.h"
#include "Texture.h"

#include <map>


class Resource
{
public:
	Resource();
	virtual ~Resource();

	//::.. GET FUNCTIONS ..:://

private:
	std::map<std::string, Level*>		m_levels;
	std::map<std::string, Mesh*>		m_meshes;
//	std::map<std::string, Shader*>		m_shaders;

};

#endif // !__RESOURCE_H__