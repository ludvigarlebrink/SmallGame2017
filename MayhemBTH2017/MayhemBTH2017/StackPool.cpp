#include "StackPool.h"



//::.. CONSTRUCTORS ..:://
StackPool::StackPool()
{
	// Do nothing...
}

StackPool::StackPool(Marker marker)
{
	InitMemory(marker);
}

StackPool::~StackPool()
{
	// Do nothing...
}


//::.. ALLOCATE FUNCTIONS ..:://
void * StackPool::Alloc(U32 sizeBytes)
{
	Marker tempMarker = m_currentMarker;
	m_currentMarker += sizeBytes;
	return (void*)tempMarker;
}


//::.. GET FUNCTIONS ..:://
StackPool::Marker StackPool::GetMarker()
{
	return m_currentMarker;
}


//::.. FREE MEMORY FUNCTIONS ..:://
void StackPool::FreeToMarker(Marker marker)
{
	m_currentMarker = marker;
}

void StackPool::Clear()
{
	m_currentMarker = m_marker;
}

void StackPool::InitMemory(Marker marker)
{
	m_marker = marker;
	m_currentMarker = m_marker;
}
