#ifndef __ARENDERABLE_H__
#define __ARENDERABLE_H__


#include "AGameObject.h"


class ARenderable : public AGameObject 
{
public:
	ARenderable();
	virtual ~ARenderable();
	
	virtual void Render();



};


#endif