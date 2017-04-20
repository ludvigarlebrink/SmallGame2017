#include "Material.h"


Material::Material()
{
	m_textureName = "NoTextureName";
	m_normalMapName = "NoNormalMapName";
}

Material::Material(const char * textureName, const char * filepath)
{
	SetTexture(textureName, filepath);
}

Material::~Material()
{
}

void Material::SetTexture(const char * textureName, const char * filepath)
{
	m_textureName = textureName;

	TextureManager::Get().AddTexture(m_textureName, filepath);
}

void Material::SetNormalMap(const char * textureName, const char * filepath)
{
	m_normalMapName = textureName;

	TextureManager::Get().AddTexture(m_normalMapName, filepath);
}

GLuint Material::GetTextureID()
{
	return TextureManager::Get().GetTextureID(m_textureName);
}

GLuint Material::GetNormalMapID()
{
	return TextureManager::Get().GetTextureID(m_normalMapName);
}
