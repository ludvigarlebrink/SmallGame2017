#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__


#include "InputManager.h"
#include "Level.h"
#include "Timer.h"
#include "TextureHandler.h"
#include "LevelHandler.h"
#include "LevelMarker.h"
#include "StateManager.h"


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
	InputManager *		m_input;
	StateManager *		m_stateManager;

	Level				m_level;
	LevelHandler		m_levelHandler;
	LevelMarker			m_levelMarker;

	Camera				m_camera;
	Timer				m_timer;
};

#endif // __LEVELEDITOR_H__