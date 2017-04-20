#ifndef __MATERIAL_H__
#define __MATERIAL_H__


#include "ShaderManager.h"
#include "TextureManager.h"


class Material
{
public:
	//::.. CONSTRUCTORS ..:://
	Material();
	Material(const char * shaderName);
	virtual ~Material();


	void Bind();
	void Free();

	//::.. SET FUNCTIONS ..:://
	void SetTexture(const char * textureName, const char * filepath);
	void SetNormalMap(const char * textureName, const char * filepath);

	//::.. GET FUNCTIONS ..:://
	GLuint GetTextureID();
	GLuint GetNormalMapID();
	GLuint GetProgramID();


private:
	const char * m_textureName;
	const char * m_normalMapName;
	const char * m_shader;
};

#endif // !__MATERIAL_H__