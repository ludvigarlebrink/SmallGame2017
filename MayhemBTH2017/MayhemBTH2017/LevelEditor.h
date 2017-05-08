#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__


#include "Level.h"
#include "Timer.h"
#include "TimeManager.h"
#include "LevelHandler.h"
#include "LevelMarker.h"
#include "StateManager.h"
#include "VirtualKeyboard.h"
#include "LevelEditorStateMachine.h"
#include "LevelTexture.h"
#include "Thumbnail.h"
#include "VideoManager.h"


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
	void Reset();
	void AxisMove();
	void ButtonInput();

private:
	enum State
	{	
		EDIT,
		MENU,
		SAVE,
		LOAD
	};

	glm::vec2					m_u = glm::vec2(0,0);

	InputManager *				m_input;
	StateManager *				m_stateManager;
	TimeManager *				m_timeManager;

	uint32_t					m_state;

	Level						m_level;
	LevelHandler				m_levelHandler;
	LevelMarker					m_levelMarker;
	LevelEditorStateMachine		m_levelGUI;
	VirtualKeyboard				m_virtualKeyboard;

	UIText						m_menuText[3];
	UIImage						m_fill;
	uint32_t					m_textPos = 0;

	Camera						m_camera;
	Timer						m_timer;
	VideoManager	*			m_videoManager;
};

#endif // ! __LEVELEDITOR_H__