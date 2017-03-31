#ifndef __IOMANAGER_H__
#define __IOMANAGER_H__


#include <string>
#include <fstream>


#include "Vector.h"


class IOManager
{
public:
	static bool ReadFile(std::string filePath, std::vector<unsigned char>& buffer);
};



#endif