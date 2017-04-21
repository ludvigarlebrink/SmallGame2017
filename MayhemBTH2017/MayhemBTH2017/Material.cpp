#include "Material.h"


Material::Material()
{
	m_textureName = "NoTextureName";
	m_normalMapName = "NoNormalMapName";
}

Material::Material(std::string programName, std::string * shaders, uint32_t * shaderTypes, uint32_t numShaders)
{
	m_shaderName = programName;

	ShaderManager::CreateAndAttachShaders(programName, shaders, shaderTypes, numShaders);
}

Material::~Material()
{
}

void Material::Bind()
{
	ShaderManager::Bind(m_shaderName.c_str());
}

void Material::Free()
{
	glDeleteProgram(ShaderManager::GetProgram(m_shaderName.c_str()));
}

void Material::SetTexture(const char * textureName, const char * filepath)
{
	m_textureName = textureName;

	TextureManager::AddTexture(m_textureName, filepath);

	m_textureID = TextureManager::Get().GetTextureID(m_shaderName.c_str());
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
	if (ShaderManager::GetProgram(m_shaderName.c_str()) != 0)
	{
		return ShaderManager::GetProgram(m_shaderName.c_str());
	}

	return 0;
}
