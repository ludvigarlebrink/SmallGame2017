#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__


#include <string>
#include <fstream>


#include "Vector.h"


class FileManager
{
public:
	bool FileManager::ReadFile(std::string filePath, std::vector<unsigned char>& buffer);
};


#endif
