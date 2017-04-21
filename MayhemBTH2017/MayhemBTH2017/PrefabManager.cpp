#include "PrefabManager.h"

#include "AnimClip.h"
#include <iostream>

uint32_t PrefabManager::numPrefabs = 0;
Prefab * PrefabManager::prefabs = nullptr;

//::.. DUMMY CONSTRUCTORS ..:://
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

Prefab * PrefabManager::Instantiate(const char * name)
{
	// Check cache first
	// Temp file path

	// Fix this search
	for (uint32_t i = 0; i < numPrefabs; i++)
	{

	}

	const char* filepath = ".\\Assets\\Prefabs\\New.mr";

	//temp for mrHandler

	mr::MrMeshHandler meshHandler;
	meshHandler.Import(filepath);

	Vertex3D * verts = new Vertex3D[meshHandler.GetNumVerts()];

	for (uint32_t i = 0; i < meshHandler.GetNumVerts(); i++)
	{
		verts[i].position = meshHandler.GetPositions()[i];
		verts[i].normal = meshHandler.GetNormals()[i];
		verts[i].texCoordsAlpha = glm::vec3(meshHandler.GetTexCoords()[i], 1.0f);
	}

	Mesh * mesh = new Mesh;
	mesh->Load(verts, meshHandler.GetNumVerts());

	Prefab * pre = new Prefab;
	pre->SetMesh(mesh);

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

void PrefabManager::Copy()
{

}
