#include "ShaderImporter.h"



ShaderImporter::ShaderImporter()
{
	// Do nothing...
}


ShaderImporter::~ShaderImporter()
{
	// Do nothing...
}

String& ShaderImporter::LoadShader(const String & filepath)
{
	std::ifstream in(filepath.GetAsCStr());

	String output;
	std::string line;

	while (in.good())
	{
		std::getline(in, line);
		output.Append(line);
	}

	return output;
}
