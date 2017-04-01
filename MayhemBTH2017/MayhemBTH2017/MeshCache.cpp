#include "MeshCache.h"



MeshCache::MeshCache()
{

}

MeshCache::~MeshCache()
{

}

Mesh& MeshCache::GetMesh(const String& name)
{
	for (size_t i = 0; i < m_key.GetSize(); i++)
	{
		if (m_key[i] == name)
		{
			return m_mesh[i];
		}
	}

	// Load Mesh;
	Mesh mesh;

	return mesh;
}


bool MeshCache::LoadMesh()
{
	return true;
}
