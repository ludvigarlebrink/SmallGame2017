#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__


#include "InputManager.h"
#include "LevelEditorLevel.h"


#include <glm.hpp>
#include <cstdint>


class LevelEditor
{
public:
	const static int SIZE_X = 16;
	const static int SIZE_Y = 16;

	//::.. CONSTRUCTORS ..:://
	LevelEditor();
	virtual ~LevelEditor();

	//::.. UPDATE FUNCTIONS ..:://
	void Update();

private:
	//::.. HELP FUNCTIONS ..:://
	void Move();
	void ClampPos();


private:
	InputManager *		m_input;	

	LevelEditorLevel	m_level;

	uint32_t			m_posX;
	uint32_t			m_posY;

};

#endif // __LEVELEDITOR_H__