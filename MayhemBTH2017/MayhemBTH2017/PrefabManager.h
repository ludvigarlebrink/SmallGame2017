#ifndef __PREFABMANAGER_H__
#define __PREFABMANAGER_H__


#include "Prefab.h"


#include <MrHandler.h>




class PrefabManager
{
public:
	static const uint32_t POOL_SIZE = 32;

	PrefabManager();
	virtual ~PrefabManager();

	static Prefab * Instantiate(const char * name);

	static bool Destroy(Prefab * prefab);

private:
	void Load();
	void Copy();

private:
	static uint32_t numPrefabs;
	static Prefab * prefabs;



};


#endif // ! __PREFABMANAGER_H__