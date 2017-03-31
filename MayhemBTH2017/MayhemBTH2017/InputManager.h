#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__


#include <SDL.h>

enum class Button
{
	// Face buttons
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,

	// Sticks
	RIGHT_STICK,
	LEFT_STICK,
	D_PAD_UP,
	D_PAD_DOWN,
	D_PAD_LEFT,
	D_PAD_RIGHT,

	// Bumpers
	RIGHT_BUMPER,
	LEFT_BUMPER,

	// Triggers
	RIGHT_TRIGGER,
	LEFT_TRIGGER,

	// Menu
	START_BUTTON,
	BACK_BUTTON
};

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
	void GetButtonInput(Button button);

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