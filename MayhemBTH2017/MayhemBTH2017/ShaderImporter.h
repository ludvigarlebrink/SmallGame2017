#ifndef __SHADERIMPORTER_H__
#define __SHADERIMPORTER_H__


#include "Shader.h"

#include <map>
#include <fstream>
#include <string>

class ShaderImporter
{
public:
	ShaderImporter();
	virtual ~ShaderImporter();

	Shader& LoadShader(char* filepath);

private:

};


#endif