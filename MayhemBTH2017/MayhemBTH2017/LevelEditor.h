#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__


#include "Level.h"
#include "Timer.h"
//#include "TextureHandler.h"
#include "LevelHandler.h"
#include "LevelMarker.h"
#include "StateManager.h"
#include "VirtualKeyboard.h"
#include "LevelEditorGUI.h"


#include <glm.hpp>
#include <cstdint>



class LevelEditor
{
public:
	const static int SIZE_X = 84;
	const static int SIZE_Y = 48;

	//::.. CONSTRUCTORS ..:://
	LevelEditor();
	virtual ~LevelEditor();

	//::.. UPDATE FUNCTIONS ..:://
	void Update();

private:
	//::.. HELP FUNCTIONS ..:://
	void AxisMove();
	void ButtonInput();
	void Reset();

private:
	enum State
	{	
		EDIT,
		MENU,
		SAVE
	};

	glm::vec2				m_u = glm::vec2(0,0);

	InputManager *		m_input;
	StateManager *		m_stateManager;

	uint32_t			m_state;

	Level				m_level;
	LevelHandler		m_levelHandler;
	LevelMarker			m_levelMarker;
	LevelEditorGUI		m_levelGUI;

	Camera				m_camera;
	Timer				m_timer;
	VirtualKeyboard		m_vk;
};

#endif // ! __LEVELEDITOR_H__