#ifndef __MATERIAL_H__
#define __MATERIAL_H__


#include "ShaderManager.h"
#include "TextureManager.h"


class Material
{
public:
	//::.. CONSTRUCTORS ..:://
	Material();
	Material(std::string programName, std::string * shaders, uint32_t * shaderTypes, uint32_t numShaders);
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
	std::string  m_shaderName;
	GLuint		 m_textureID;

};

#endif // !__MATERIAL_H__