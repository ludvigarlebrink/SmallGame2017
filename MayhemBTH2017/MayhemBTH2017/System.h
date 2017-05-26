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
#include "Mesh.h"
#include "MenuSystem.h"
#include "UIText.h"
#include "Prefab.h"
#include "PrefabManager.h"
#include "GamePhysics.h"
#include "GameUI.h"
#include "UIImage.h"
#include "GameSystem.h"
#include "TransitionManager.h"
#include "AntiAliasing.h"
#include "MeshQuad.h"
#include "Background.h"



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
	void Free();

private:
	VideoManager *	m_videoManager;
	InputManager *	m_inputManager;
	TimeManager *	m_timeManager;
	StateManager *	m_stateManager;
	SoundManager *	m_soundManager;

	MenuSystem *	m_menuSystem;
	Background *	m_background;
	LevelEditor *	m_levelEditor;
	GameSystem *	m_gameSystem;
};


#endif // __SYSTEM_H__