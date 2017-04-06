#ifndef  __LEVELEXPORTER_H__
#define __LEVELEXPORTER_H__

#include "Level.h"
#include <fstream>
#include <iostream>

class LevelExporter
{
public:

	//::.. DUMMY CONSTRUCTORS ..:://
	LevelExporter();
	virtual ~LevelExporter();

	//::.. EXPORT ..:://
	void Export(Level &level);


private:
	std::ofstream	m_fileName;
};

#endif