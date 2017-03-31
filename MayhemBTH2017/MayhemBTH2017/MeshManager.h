#ifndef __MESHMANAGER_H__
#define __MESHMANAGER_H__


#include "Mesh.h"


class MeshManager
{
public:
	MeshManager();
	virtual ~MeshManager();

	void StartUp();
	void ShutDown();

private:
	static MeshManager * meshManager;
};


#endif