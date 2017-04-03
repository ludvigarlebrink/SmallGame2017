#ifndef __STACKALLOCATOR_H__
#define __STACKALLOCATOR_H__


#include <cstdlib>
#include <cstdint>

 
class StackPool
{
public:
	//::.. TYPEDEF ..:://
	typedef intptr_t U32;
	typedef intptr_t Marker;

	//::.. CONSTRUCTORS ..:://
	StackPool();
	StackPool(Marker marker);
	virtual ~StackPool();		// Destructor.

	//::.. POOL FUNCTIONS ..:://
	void InitMemory(Marker marker);
	void* Alloc(U32 sizeBytes);

	//::.. GET FUNCTIONS ..:://
	Marker GetMarker();

	//::.. FREE MEMORY FUNCTIONS ..:://
	void FreeToMarker(Marker marker);
	void Clear();

private:
	Marker m_marker;
	Marker m_currentMarker;
};


#endif