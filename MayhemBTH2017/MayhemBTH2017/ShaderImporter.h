#ifndef __SHADERIMPORTER_H__
#define __SHADERIMPORTER_H__


#include "Shader.h"


#include <glew.h>
#include <map>
#include <fstream>
#include <string>
#include <iostream>


namespace imp 
{
	class ShaderImporter
	{
	public:
		//::.. CONSTRUCTORS ..:://
		ShaderImporter();								// Defualt constructor.
		ShaderImporter(const ShaderImporter& object);	// Copy constructor.
		virtual ~ShaderImporter();

		//::.. OPERATOR OVERLOADING ..:://



		Shader& Get(const char* filepath);

	private:
		//::.. HELP FUNCTIONS ..:://
		Shader& Import(const char* filepath);
		void CreateShader(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg);
		void Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg);

	private:
		std::map<std::string, Shader*>	m_shaderCache;
	};
}

#endif