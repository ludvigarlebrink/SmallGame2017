#ifndef __MESHIMPORTER_H__
#define __MESHIMPORTER_H__


#include "Mesh.h"
#include "StackPool.h"

class MeshImporter
{
public:
	MeshImporter();
	virtual ~MeshImporter();

	Mesh& ImportMesh();

private:
	//::.. HELP FUNCTIONS ..:://
	void ImportPositions();
	void ImportNormals();
	void ImportTexCoords();
	
};


#endif