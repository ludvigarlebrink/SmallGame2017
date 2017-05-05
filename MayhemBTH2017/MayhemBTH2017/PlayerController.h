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

struct Axis
{
	float axisDeadzone;
	float axisRaw;
};

enum ButtonInput
{
	CONTROLLER_BUTTON_A = 0,
	CONTROLLER_BUTTON_B,
	CONTROLLER_BUTTON_X,
	CONTROLLER_BUTTON_Y,
	CONTROLLER_BUTTON_BACK,
	CONTROLLER_BUTTON_START,
	CONTROLLER_BUTTON_LEFTBUTTON,
	CONTROLLER_BUTTON_RIGHTBUTTON,
	CONTROLLER_BUTTON_DPAD_UP,
	CONTROLLER_BUTTON_DPAD_DOWN,
	CONTROLLER_BUTTON_DPAD_LEFT,
	CONTROLLER_BUTTON_DPAD_RIGHT,
	NUM_BUTTONS
};

enum AxisInput
{
	CONTROLLER_AXIS_LEFT_X = 0,
	CONTROLLER_AXIS_LEFT_Y,
	CONTROLLER_AXIS_RIGHT_X,
	CONTROLLER_AXIS_RIGHT_Y,
	CONTROLLER_AXIS_TRIGGERLEFT,
	CONTROLLER_AXIS_TRIGGERRIGHT,
	NUM_AXIS
};

class PlayerController
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	PlayerController();
	virtual ~PlayerController();

	//::.. MODIFY FUNCTIONS ..:://
	void Update(Sint32 playerControllerID);
	void Reset();
	void AddPlayerController(Sint32 playerControllerID);
	void RemovePlayerController();

	//::.. GET FUNCTIONS ..:://
	bool GetButtonDown(size_t button);
	bool GetButtonHeld(size_t button);
	bool GetButtonUp(size_t button);
	float GetAxis(size_t button);
	float GetAxisRaw(size_t button);
	size_t GetNumButtons();
	size_t GetNumAxis();
	Sint32 GetControllerID();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();
	void ButtonDown(Sint32 playerControllerID);
	void ButtonUp(const SDL_ControllerButtonEvent controllerEvent);
	void GetAxis(const SDL_ControllerAxisEvent controllerEvent);
	void GetAxisRaw(const SDL_ControllerAxisEvent controllerEvent);
	float ScaleRange(Sint16 value);

private:
	Button					m_button[NUM_BUTTONS];
	Axis					m_axis[NUM_AXIS];
	float					m_deadzone; //Set in Init()
	SDL_Event				m_event;
	SDL_GameController*		m_controller;
	Sint32					m_controllerID;

};

#endif