#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__


#include "InputManager.h"
#include "LevelEditorLevel.h"


#include <glm.hpp>
#include <cstdint>


class LevelEditor
{
public:
	//::.. CONSTRUCTORS ..:://
	LevelEditor();
	virtual ~LevelEditor();

	//::.. UPDATE FUNCTIONS ..:://
	void Update();

private:
	//::.. HELP FUNCTIONS ..:://
	void Move();


private:
	LevelEditorLevel	m_level;
	InputManager*		m_input;
	uint32_t			m_posX;
	uint32_t			m_posY;

};

#endif // __LEVELEDITOR_H__