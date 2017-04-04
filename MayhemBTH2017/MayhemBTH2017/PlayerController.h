#ifndef  __PLAYERCONTROLLER_H__
#define __PLAYERCONTROLLER_H__

#include <SDL.h>

//Used for debug
#include <iostream>

struct Button
{
	bool isDown;
	bool isHeld;
	bool isUp;
};

enum ControllerInput
{
	CONTROLLER_BUTTON_A = 0,
	CONTROLLER_BUTTON_B,
	CONTROLLER_BUTTON_X,
	CONTROLLER_BUTTON_Y,
	CONTROLLER_BUTTON_BACK,
	CONTROLLER_BUTTON_START,
	CONTROLLER_BUTTON_LEFTSHOULDER,
	CONTROLLER_BUTTON_RIGHTSHOULDER,
	CONTROLLER_BUTTON_DPAD_UP,
	CONTROLLER_BUTTON_DPAD_DOWN,
	CONTROLLER_BUTTON_DPAD_LEFT,
	CONTROLLER_BUTTON_DPAD_RIGHT,
	NUM_BUTTONS
};

class PlayerController
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	PlayerController();
	virtual ~PlayerController();

	//::.. MODIFY FUNCTIONS ..:://
	void Update();
	void Reset();
	void AddPlayerController(SDL_ControllerDeviceEvent PlayerControllerID);
	void RemovePlayerController();

	//::.. GET FUNCTIONS ..:://
	bool GetButtonDown(size_t button);
	bool GetButtonHeld(size_t button);
	bool GetButtonUp(size_t button);
	size_t GetNumButtons();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();
	void ButtonDown(const SDL_ControllerButtonEvent controllerEvent);
	void ButtonUp(const SDL_ControllerButtonEvent controllerEvent);
	void AxisInput(const SDL_ControllerAxisEvent controllerEvent);

private:
	Button m_button[NUM_BUTTONS];

	SDL_Event				m_event;
	SDL_GameController *	m_controller;

};

#endif