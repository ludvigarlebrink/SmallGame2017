#ifndef __TOONSHADER_H__
#define __TOONSHADER_H__


#include "AShader.h"
#include "Textures.h"

class ToonShader :
	public AShader
{
public:
	//::.. CONSTRUCTORS ..:://
	ToonShader();
	virtual ~ToonShader();


	//::.. HELP FUNCTIONS ..:://
	void UpdateUniforms(Transform& transform, Camera& camera);
	void UpdateTextures();

private:
private:
};

#endif // !__TOONSHADER_H__
