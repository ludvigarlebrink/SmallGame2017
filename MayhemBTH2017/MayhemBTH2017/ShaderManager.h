#ifndef __SHADERMANAGER_H__
#define __SHADERMANAGER_H__


#include <glew.h>
#include <cstdint>
#include <fstream>
#include <string>

#include <map>


class ShaderManager
{
public:
	enum ShaderType
	{
		NONE,
		VERT_SHADER,
		GEOM_SHADER,
		FRAG_SHADER,
		NUM_SHADERS
	};

	//::.. CONSTRUCTORS ..:://
	ShaderManager();
	virtual ~ShaderManager();

	void StartUp();

	//::.. 
	static GLuint CreateAndAttachShaders(std::string programName, std::string * shaders, uint32_t * shaderTypes, uint32_t numShaders);
	static GLuint LinkAndValidate();


	//::.. GET FUNCTIONS ..:://
	static GLuint GetProgram(const char * name);
private:
	static GLuint LoadShader(std::string shader, uint32_t shaderType);

private:
	static ShaderManager * m_instance;

	static std::map<std::string, GLuint> m_programs;

};

#endif // ! __SHADERMANAGER_H__