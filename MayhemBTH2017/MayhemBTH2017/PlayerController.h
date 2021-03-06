#ifndef  __PLAYERCONTROLLER_H__
#define __PLAYERCONTROLLER_H__

#include <SDL.h>

//Used for debug


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
	void Update();
	void Reset();
	void AddPlayerController(int playerControllerID);
	void RemovePlayerController();

	//::.. GET FUNCTIONS ..:://
	bool GetButtonDown(size_t button, uint32_t id);
	bool GetButtonHeld(size_t button, uint32_t id);
	bool GetButtonUp(size_t button, uint32_t id);
	float GetAxis(size_t button, uint32_t id);
	float GetAxisRaw(size_t button, uint32_t id);
	size_t GetNumButtons();
	size_t GetNumAxis();
	int GetControllerID_0();
	int GetControllerID_1();
	int GetControllerID_2();
	int GetControllerID_3();
	static PlayerController* GetController(int ID);

	static int GetControllerIndex(SDL_JoystickID instance);

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();
	void ButtonDown(const SDL_ControllerButtonEvent controllerEvent);
	void ButtonUp(const SDL_ControllerButtonEvent controllerEvent);
	void GetAxis(const SDL_ControllerAxisEvent controllerEvent);
	void GetAxisRaw(const SDL_ControllerAxisEvent controllerEvent);
	float ScaleRange(Sint16 value);

private:
	Button						m_button[NUM_BUTTONS];
	Axis						m_axis[NUM_AXIS];
	float						m_deadzone; //Set in Init()
	SDL_Event					m_event;
	SDL_GameController *		m_controller;
	SDL_Haptic *				m_haptic;
	SDL_JoystickID				m_controllerID;
	bool						m_isConnected;
	static PlayerController	*	m_controllers;


};

#endif