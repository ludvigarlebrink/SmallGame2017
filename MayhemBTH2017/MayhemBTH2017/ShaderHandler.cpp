#include "ShaderHandler.h"



ShaderHandler::ShaderHandler()
{
	// Do nothing...
}


ShaderHandler::~ShaderHandler()
{
	// Do nothing...
}




void ShaderHandler::CreateShader(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMsg)
{

}


void ShaderHandler::Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg)
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
