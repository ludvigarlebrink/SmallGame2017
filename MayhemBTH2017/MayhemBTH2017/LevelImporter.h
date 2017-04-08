#ifndef  __LEVELIMPORTER_H__
#define __LEVELIMPORTER_H__

#include "Level.h"

#include <fstream>


class LevelImporter
{
public:
	LevelImporter();
	virtual ~LevelImporter();


	void ImportLevel(Level & level);

private:
	std::ifstream	m_fileName;
};

#endif // ! __LEVELIMPORTER_H__