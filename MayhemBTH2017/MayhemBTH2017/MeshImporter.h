#ifndef __MESHIMPORTER_H__
#define __MESHIMPORTER_H__

#include "Mesh.h"
#include "StackPool.h"

//Assimp
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include <fstream>
#include <iostream>

#include <vector>

class MeshImporter
{
public:
	MeshImporter();
	virtual ~MeshImporter();

	void ImportFromFile();


private:
	Assimp::Importer importer;
	const aiScene * scene = NULL;
	Mesh m_mesh;
	
};


#endif