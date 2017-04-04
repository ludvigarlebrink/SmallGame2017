#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__


#include "LevelEditorLevel.h"


#include <glm.hpp>
#include <cstdint>


class LevelEditor
{
public:
	//::.. CONSTRUCTORS ..:://
	LevelEditor();
	virtual ~LevelEditor();

	void Update();


private:

private:
	uint32_t m_posX;
	uint32_t m_posY;
	LevelEditorLevel m_level;

};

#endif // __LEVELEDITOR_H__