#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__


#include <SDL.h>


class InputManager
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	InputManager();
	virtual ~InputManager();

	//::.. FAKE CONSTRUCTORS ..:://
	void StartUp();
	void ShutDown();

	void Update();

	//::.. GET FUNCTIONS ..:://
	InputManager& Get();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	//::.. CONSTANT VARIABLES ..:://
	static const uint8_t	MAX_PLAYERS = 1;

	static InputManager *	m_instance;

	SDL_Event				m_event;
	SDL_GameController *	m_controller[MAX_PLAYERS];
	uint8_t					m_controllerCount;
};


#endif