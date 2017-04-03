#ifndef __DEFAULTALLOCATOR_H__
#define __DEFAULTALLOCATOR_H__


#include "AAllocator.h"


class DefaultAllocator : public AAllocator
{
public:
	//::.. CONSTRUCTORS ..:://
	DefaultAllocator();
	virtual ~DefaultAllocator();

	virtual void* Alloc(U32 sizeBytes) override;

	virtual void Clear() override;

private:

	
};


#endif