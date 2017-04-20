#include "Material.h"


Material::Material()
{
	m_textureName = "NoTextureName";
	m_normalMapName = "NoNormalMapName";
}

Material::Material(const char* shaderName)
{
	m_shader = shaderName;
}

Material::~Material()
{
}

void Material::SetTexture(const char * textureName, const char * filepath)
{
	m_textureName = textureName;

	TextureManager::AddTexture(m_textureName, filepath);
}

void Material::SetNormalMap(const char * textureName, const char * filepath)
{
	m_normalMapName = textureName;

	TextureManager::AddTexture(m_normalMapName, filepath);
}

GLuint Material::GetTextureID()
{
	return TextureManager::GetTextureID(m_textureName);
}

GLuint Material::GetNormalMapID()
{
	return TextureManager::GetTextureID(m_normalMapName);
}

GLuint Material::GetProgramID()
{
	if (ShaderManager::GetProgram(m_shader) != 0)
	{
		return ShaderManager::GetProgram(m_shader);
	}

	return 0;
}
