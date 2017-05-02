#include "ShaderManager.h"
#include <iostream>


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
	GLuint programID = glCreateProgram();

	m_programs[programName] = programID;

	GLuint * shader = new GLuint[numShaders];

	for (uint32_t i = 0; i < numShaders; i++)
	{
		shader[i] = SetShader(shaders[i], shaderTypes[i]);
		glAttachShader(programID, shader[i]);
	}
	
	return m_programs[programName];
}

GLuint ShaderManager::LinkAndValidate(const char * programName)
{
	GLuint hej = m_programs[programName];
	glLinkProgram(m_programs[programName]);
	Debug(m_programs[programName], GL_LINK_STATUS, true, "Error: Linking failed: ");

	glValidateProgram(m_programs[programName]);
	Debug(m_programs[programName], GL_VALIDATE_STATUS, true, "Error: Invalid program: ");

	return m_programs[programName];
}

void ShaderManager::Bind(const char * programName)
{
	glUseProgram(ShaderManager::GetProgram(programName));
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

GLuint ShaderManager::CreateShader(std::string & textfile, GLenum shaderType)
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
	Debug(shader, GL_COMPILE_STATUS, false, "Compilation failed\n");

	return shader;
}


void ShaderManager::Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg)
{

	GLint errorCheck = 0;
	GLchar logLength[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &errorCheck);
	}
	else
	{
		glGetShaderiv(shader, flag, &errorCheck);
	}

	if (errorCheck == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(logLength), 0, logLength);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(logLength), 0, logLength);
		}

		std::cout << errorMsg << ": '" << logLength << "'" << std::endl;
	}
}