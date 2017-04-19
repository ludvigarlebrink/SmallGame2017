#include "PrefabManager.h"



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

Prefab * PrefabManager::Instantiate(const char * name)
{
	// Check cache first
	// Temp file path

	// Fix this search
	for (uint32_t i = 0; i < numPrefabs; i++)
	{

	}

	const char* filepath = ".\\Assets\\Prefabs\\Test.mr";

//	m_handler->Import(filepath);
	mr::MrHandler handler;
//	handler.GetSkelHandlers()->

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
