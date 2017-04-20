#ifndef __SHADERMANAGER_H__
#define __SHADERMANAGER_H__


#include <glew.h>
#include <cstdint>


#include <vector>


class ShaderManager
{
public:
	enum ShaderType
	{
		NONE,
		VERT_SHADER,
		GEOM_SHADER,
		FRAG_SHADER
	};

	//::.. CONSTRUCTORS ..:://
	ShaderManager();
	virtual ~ShaderManager();

	//::.. 
	static GLuint CreateAndAttachShaders(const char* name1, uint32_t shaderType1,
		const char* name2, uint32_t shaderType2,
		const char* name3, uint32_t shaderType3);

	static GLuint LinkAndValidate();



	//::.. GET FUNCTIONS ..:://
	static void GetProgram(const char * name);
private:
	GLuint Search(const char* name1);

private:
	struct Program
	{
		bool			isLoaded;
		const char *	name;
		GLuint			program;
	};

	std::vector<Program> m_programs;

};

#endif // ! __SHADERMANAGER_H__