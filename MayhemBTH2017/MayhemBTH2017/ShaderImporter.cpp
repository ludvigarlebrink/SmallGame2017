#include "ShaderImporter.h"


namespace imp
{
	ShaderImporter::ShaderImporter()
	{
		// Do nothing...
	}


	ShaderImporter::~ShaderImporter()
	{
		// Do nothing...
	}

	Shader & ShaderImporter::Get(const char * filepath)
	{
		return Shader();
	}

	//::.. HELP FUNCTIONS ..:://
	Shader& ShaderImporter::Import(const char* filepath)
	{
		std::ifstream in(filepath);

		std::string output;
		std::string line;

		while (in.good())
		{
			std::getline(in, line);
			output.append(line);
		}

		//	return output;
		return Shader();

	}

	void ShaderImporter::CreateShader(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMsg)
	{

	}

	void ShaderImporter::Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg)
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
}