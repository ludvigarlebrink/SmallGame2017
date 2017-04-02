#ifndef __AALLOCATOR_H__
#define __AALLOCATOR_H__


#include <cstdlib>
#include <cstdint>


class AAllocator
{
public:
	//::.. TYPEDEF ..:://
	typedef intptr_t U32;
	typedef intptr_t Marker;

	//::.. CONSTRUCTORS ..:://
	AAllocator() {};
	virtual ~AAllocator() {};

	virtual void* Alloc(U32 sizeBytes) = 0;
	virtual void Clear() = 0;
};


#endif // __ALLOCATOR_H__