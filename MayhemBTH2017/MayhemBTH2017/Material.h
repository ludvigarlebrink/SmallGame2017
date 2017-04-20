#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "ShaderManager.h"
#include "TextureManager.h"


class Material
{
public:
	//::.. CONSTRUCTORS ..:://
	Material();
	Material(const char * textureName, const char * filepath);
	virtual ~Material();

	//::.. SET FUNCTIONS ..:://
	void SetTexture(const char * textureName, const char * filepath);
	void SetNormalMap(const char * textureName, const char * filepath);

	//::.. GET FUNCTIONS ..:://
	GLuint GetTextureID();
	GLuint GetNormalMapID();

private:
	const char * m_textureName;
	const char * m_normalMapName;
};

#endif // !__MATERIAL_H__