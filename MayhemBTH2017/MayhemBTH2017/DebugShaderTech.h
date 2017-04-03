#ifndef __SHADERDEBUG_H__
#define __SHADERDEBUG_H__


#include "AShader.h"


class DebugShaderTech :	public AShader
{
public:
	//::..CONSTRUCTORS..:://
	DebugShaderTech();
	virtual ~DebugShaderTech();

	virtual void Update(Transform transform, Camera camera);

protected:


private:
};

#endif // !__SHADERDEBUG_H__
