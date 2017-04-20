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

	GLuint shader[NUM_SHADERS];

	for (uint32_t i = 0; i < numShaders; i++)
	{
		shader[i] = SetShader(shaders[i], shaderTypes[i]);

		glAttachShader(m_programs[programName], shader[i]);
	}
	
	return 0;
}

GLuint ShaderManager::LinkAndValidate()
{

	return false;
}


GLuint ShaderManager::GetProgram(const char * name)
{
	return m_programs[name];
}


GLuint ShaderManager::SetShader(std::string shader, uint32_t shaderType)
{

	GLuint shaderTemp;

	switch (shaderType)
	{
	case NONE:
		shaderTemp = 0;
		break;

	case VERT_SHADER:
		shaderTemp = CreateShader(LoadShader(shader), GL_VERTEX_SHADER);
		break;

	case GEOM_SHADER:
		shaderTemp = CreateShader(LoadShader(shader), GL_GEOMETRY_SHADER);
		break;

	case FRAG_SHADER:
		shaderTemp = CreateShader(LoadShader(shader), GL_FRAGMENT_SHADER);
		break;

	default:
		break;
	}

	return shaderTemp;
}

std::string ShaderManager::LoadShader(const std::string & filename)
{
	std::ifstream in(filename.c_str());

	std::string output;
	std::string line;

	if (in.is_open())
	{
		while (in.good())
		{
			getline(in, line);
			output.append(line + '\n');
		}
	}

	return output;
}

GLuint ShaderManager::CreateShader(const std::string & textfile, GLenum shaderType)
{

	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		//std::cout << "Error while creating shader" << std::endl;
	}

	const GLchar* shaderSource[1];
	GLint sourceLength[1];

	shaderSource[0] = textfile.c_str();
	sourceLength[0] = textfile.length();

	glShaderSource(shader, 1, shaderSource, sourceLength);
	glCompileShader(shader);
	//Debug(shader, GL_COMPILE_STATUS, false, "Compilation failed\n");

	return shader;
}
