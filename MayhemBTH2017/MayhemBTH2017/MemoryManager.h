#ifndef __MEMORYMANAGER_H__
#define __MEMORYMANAGER_H__


#include "StackPool.h"


#include <cstdlib>
#include <cstdint>


class MemoryManager
{
public:
	//::.. TYPEDEF ..:://
	typedef intptr_t U32;
	typedef intptr_t Marker;

	//::.. DUMMY CONSTRUCTORS ..:://
	MemoryManager();

	// Deconstructor.
	virtual ~MemoryManager();

	//::.. FAKE CONSTRUCTORS ..:://
	void StartUp();
	void ShutDown();

	//::.. GET FUNCTIONS ..:://
	MemoryManager& Get();
	StackPool& GetMeshPool();
	StackPool& GetTexturePool();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	static const U32 MEMORY_SIZE = 1024*1024*10;
	
	static MemoryManager* m_instance;

	Marker m_marker;
	Marker m_currentMarker;

	StackPool m_meshPool;
	StackPool m_texturePool;
};


#endif