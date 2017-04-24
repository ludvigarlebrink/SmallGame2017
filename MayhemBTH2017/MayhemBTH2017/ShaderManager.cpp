#include "ShaderManager.h"

ShaderManager * ShaderManager::m_instance = nullptr;

std::map<std::string, GLuint> ShaderManager::m_programs = { { "none", GLuint() } };

ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{

}

void ShaderManager::StartUp()
{

	if (m_instance == nullptr)
	{
		m_instance = this;
	}

}

GLuint ShaderManager::CreateAndAttachShaders(std::string programName, std::string * shaders, uint32_t * shaderTypes, uint32_t numShaders)
{
	m_programs.insert(std::pair<std::string, GLuint>(programName, glCreateProgram()));


	for (uint32_t i = 0; i < numShaders; i++)
	{
		m_programs[programName] = LoadShader(shaders[i], shaderTypes[i]);
	}

	return 0;
}

GLuint ShaderManager::LinkAndValidate()
{

	return false;
}


GLuint ShaderManager::GetProgram(const char * name)
{
	return 0;
}


GLuint ShaderManager::LoadShader(std::string shader, uint32_t shaderType)
{

	switch (shaderType)
	{
	case NONE:
		break;

	case VERT_SHADER:
		break;

	case GEOM_SHADER:
		break;

	case FRAG_SHADER:
		break;

	default:
		break;
	}

	return 0;
}