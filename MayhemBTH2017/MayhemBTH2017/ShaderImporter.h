#ifndef __SHADERIMPORTER_H__
#define __SHADERIMPORTER_H__


#include "String.h"

#include <fstream>
#include <string>

class ShaderImporter
{
public:
	ShaderImporter();
	virtual ~ShaderImporter();

	String& LoadShader(const String &filepath);

private:

};


#endif