#include "FileManager.h"


bool FileManager::ReadFile(std::string filePath, Vector<unsigned char>& buffer)
{
	std::ifstream file(filePath.c_str(),   std::ios::binary);

	if (file.fail())
	{
		// failed to load file.
		return false;
	}
	
	file.seekg(0, std::ios::end);

	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	fileSize -= file.tellg();
	
	buffer.Resize(fileSize);

	file.read((char*)&buffer[0], fileSize);

	file.close();

	return false;
}
