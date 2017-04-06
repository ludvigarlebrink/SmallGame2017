#ifndef  __LEVELIMPORTER_H__
#define __LEVELIMPORTER_H__

#include <fstream>

class LevelImporter
{
public:
	LevelImporter();
	virtual ~LevelImporter();
	void ImportLevel();

private:
	std::ifstream m_fileName;
};

#endif // ! __LEVELIMPORTER_H__