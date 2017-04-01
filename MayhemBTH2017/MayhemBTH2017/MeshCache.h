#ifndef __MESHCACHE_H__
#define __MESHCACHE_H__


#include "Vector.h"
#include "String.h"
#include "Mesh.h"


class MeshCache
{
public:
	MeshCache();
	virtual ~MeshCache();
	
	//::.. GET FUNCTIONS ..:://
	Mesh& GetMesh(const String& filepath);

private:
	bool LoadMesh();

private:
	Vector<String>	m_key;
	Vector<Mesh>	m_mesh;

	
};


#endif // __RESOURCECACHE_H__