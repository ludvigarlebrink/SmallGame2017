#include "ShaderImporter.h"



ShaderImporter::ShaderImporter()
{
	// Do nothing...
}


ShaderImporter::~ShaderImporter()
{
	// Do nothing...
}

Shader& ShaderImporter::LoadShader(char* filepath)
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
