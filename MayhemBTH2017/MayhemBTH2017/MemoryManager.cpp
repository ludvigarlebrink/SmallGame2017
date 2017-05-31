#include "MemoryManager.h"



MemoryManager * MemoryManager::m_instance = nullptr;


//::.. DUMMY CONSTRUCTORS ..:://
MemoryManager::MemoryManager()
{
	// Do nothing...
}

MemoryManager::~MemoryManager()
{
	// Do nothing...
}


//::.. FAKE CONSTRUCTORS ..:://
void MemoryManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
		Init();
	}
}

void MemoryManager::ShutDown()
{
	free((void*)m_marker);
}

MemoryManager & MemoryManager::Get()
{
	return *m_instance;
}

StackPool& MemoryManager::GetMeshPool()
{
	return m_meshPool;
}

StackPool& MemoryManager::GetTexturePool()
{
	return m_texturePool;
}

//::.. HELP FUNCTIONS ..:://
void MemoryManager::Init()
{
	// Allocating heap memory.
	m_marker = (Marker)malloc(MEMORY_SIZE);
	m_currentMarker = m_marker;

	m_meshPool.InitMemory(m_currentMarker);
	m_currentMarker += MEMORY_SIZE;

	m_texturePool.InitMemory(m_currentMarker);
	m_currentMarker += MEMORY_SIZE;
}
