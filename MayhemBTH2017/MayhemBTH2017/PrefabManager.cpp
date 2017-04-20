#include "PrefabManager.h"

#include "AnimClip.h"
#include <iostream>

uint32_t PrefabManager::numPrefabs = 0;
Prefab * PrefabManager::prefabs = nullptr;


PrefabManager::PrefabManager()
{
	// Do nothing...
	// TEMP
	prefabs = new Prefab[POOL_SIZE];
}


PrefabManager::~PrefabManager()
{
	// Do nothing...
}

Prefab * PrefabManager::Instantiate(const char * name, MeshInfo t)
{
	// Check cache first
	// Temp file path

	// Fix this search
	for (uint32_t i = 0; i < numPrefabs; i++)
	{

	}

	const char* filepath = ".\\Assets\\Prefabs\\T.mr";

	mr::MrHandler handler;

	glm::vec3 * test;

	mr::MrMeshHandler meshHandler;
	meshHandler.Import(filepath);

	test = meshHandler.GetPositions();

	t.numVerts = meshHandler.GetNumVerts();
	t.vertPos = meshHandler.GetPositions();


	std::cout << test[0].x << " " << test[0].y<< " " << test[0].z << std::endl;


	//KeyFrame key;
	//key.localTx = anim[0].GetKeyFramedJoints()->matrix;
	//Prefab pre;
	//Mesh mesh;
	//pre.SetMesh(mesh);



	return nullptr;
}

bool PrefabManager::Destroy(Prefab * prefab)
{
	return false;
}


//::.. HELP FUNCTIONS ..:://
void PrefabManager::Load()
{
}
