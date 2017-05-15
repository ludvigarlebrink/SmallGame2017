#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "LevelEditor.h"
#include "VideoManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "StateManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "PostProcessingManager.h"

#include "AntiAliasing.h"
#include "MeshQuad.h"


class System
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	System();
	virtual ~System();

	//::.. THE MAIN LOOP ..:://
	void Run();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	VideoManager *	m_videoManager;
	InputManager *	m_inputManager;
	TimeManager *	m_timeManager;
	StateManager*	m_stateManager;
	SoundManager*	m_soundManager;

};


#endif // __SYSTEM_H__