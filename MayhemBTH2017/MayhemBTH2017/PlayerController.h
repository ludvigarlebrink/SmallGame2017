#ifndef  __PLAYERCONTROLLER_H__
#define __PLAYERCONTROLLER_H__

#include <SDL.h>

//Used for debug
#include <iostream>

enum ControllerInput
{
	BUTTON_A,
	BUTTON_B,
	NUM_BUTTONS
};

class PlayerController
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	PlayerController();
	virtual ~PlayerController();

	//::.. FAKE CONSTRUCTORS ..:://
	void StartUp();
	void ShutDown();

	//::.. MODIFY FUNCTIONS ..:://
	void Update();
	void AddPlayerController(SDL_ControllerDeviceEvent PlayerControllerID);
	void RemovePlayerController();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();
	void ButtonInput(const SDL_ControllerButtonEvent controllerEvent);
	void AxisInput(const SDL_ControllerAxisEvent controllerEvent);

private:
	SDL_Event				m_event;
	SDL_GameController *	m_controller;

};

#endif