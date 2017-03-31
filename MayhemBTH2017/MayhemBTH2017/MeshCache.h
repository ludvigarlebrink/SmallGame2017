#ifndef __MESHCACHE_H__
#define __MESHCACHE_H__


#include "Mesh.h"

#include <string>
#include <map>


class MeshCache
{
public:
	//::.. CONSTRUCTORS .:://
	MeshCache();
	virtual ~MeshCache();

	//::.. GET FUNCTIONS ..:://
	Mesh GetMesh(uint32_t meshID);

private:
	std::map<uint32_t, Mesh> m_meshMap;
};


#endif