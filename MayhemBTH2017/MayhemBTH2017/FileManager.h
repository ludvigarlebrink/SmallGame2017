#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__


#include <string>
#include <fstream>


#include "Vector.h"


class FileManager
{
public:
	static bool FileManager::ReadFile(std::string filePath, Vector<unsigned char>& buffer);
};


#endif
