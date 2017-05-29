#include "PlayerController.h"



PlayerController * PlayerController::m_controllers = new PlayerController[4];


PlayerController::PlayerController()
{
	Init();
	m_isConnected = false;
	m_controller = 0;
	m_controllerID = -1;
	m_haptic = 0;
}

PlayerController::~PlayerController()
{
	// Do nothing...
}

void PlayerController::Update()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_CONTROLLERDEVICEADDED:
			if (sdlEvent.cdevice.which < 4) {
				PlayerController& pController = m_controllers[sdlEvent.cdevice.which];
				pController.AddPlayerController(sdlEvent.cdevice.which);
			}
			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			RemovePlayerController();
			break;

		case SDL_CONTROLLERBUTTONDOWN:
			m_controllers[sdlEvent.cdevice.which].ButtonDown(sdlEvent.cbutton);
			break;

		case SDL_CONTROLLERBUTTONUP:
			m_controllers[sdlEvent.cdevice.which].ButtonUp(sdlEvent.cbutton);
			break;

		case SDL_CONTROLLERAXISMOTION:
			m_controllers[sdlEvent.cdevice.which].GetAxis(sdlEvent.caxis);
			m_controllers[sdlEvent.cdevice.which].GetAxisRaw(sdlEvent.caxis);
			break;
		}
	}
}


void PlayerController::Reset()
{
	for (uint32_t i = 0; i < 4; i++)
	{

		for (size_t j = 0; j < NUM_BUTTONS; j++)
		{
			m_controllers[i].m_button[j].isDown = false;
			m_controllers[i].m_button[j].isUp = false;
		}
	}

	
}

void PlayerController::AddPlayerController(int playerControllerID)
{
	m_controller = SDL_GameControllerOpen(playerControllerID);
	SDL_Joystick *joy = SDL_GameControllerGetJoystick(m_controller);
	m_controllerID = SDL_JoystickInstanceID(joy);
	m_isConnected = true;

	if (SDL_JoystickIsHaptic(joy)) {
		m_haptic = SDL_HapticOpenFromJoystick(joy);
		if (SDL_HapticRumbleSupported(m_haptic)) {
			if (SDL_HapticRumbleInit(m_haptic) != 0) {
				SDL_HapticClose(m_haptic);
				m_haptic = 0;
			}
		}
		else {
			SDL_HapticClose(m_haptic);
			m_haptic = 0;
		}
	}
}

void PlayerController::RemovePlayerController()
{
	if (m_isConnected) 
	{
		
		m_isConnected = false;
		
		if (m_haptic) 
		{
			SDL_HapticClose(m_haptic);
			m_haptic = 0;
		}

		SDL_GameControllerClose(m_controller);
		m_controller = 0;
	}
}


//::.. GET FUNCTIONS ..:://
bool PlayerController::GetButtonDown(size_t button, uint32_t id)
{
	return m_controllers[id].m_button[button].isDown;
}

bool PlayerController::GetButtonHeld(size_t button, uint32_t id)
{
	return m_controllers[id].m_button[button].isHeld;
}

bool PlayerController::GetButtonUp(size_t button, uint32_t id)
{
	return m_controllers[id].m_button[button].isUp;
}

float PlayerController::GetAxis(size_t axis, uint32_t id)
{
	return m_controllers[id].m_axis[axis].axisDeadzone;
}

float PlayerController::GetAxisRaw(size_t axis, uint32_t id)
{
	return m_controllers[id].m_axis[axis].axisRaw;
}

size_t PlayerController::GetNumButtons()
{
	return NUM_BUTTONS;
}

size_t PlayerController::GetNumAxis()
{
	return NUM_AXIS;
}

int PlayerController::GetControllerID_0()
{
	return m_controllers[0].GetControllerIndex(1);
}

int PlayerController::GetControllerID_1()
{
	return m_controllers[1].GetControllerIndex(2);
}

int PlayerController::GetControllerID_2()
{
	return m_controllers[2].GetControllerIndex(3);
}

int PlayerController::GetControllerID_3()
{
	return m_controllers[3].GetControllerIndex(4);
}

PlayerController * PlayerController::GetController(int ID)
{
	return &m_controllers[ID];
}

int PlayerController::GetControllerIndex(SDL_JoystickID instance)
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_controllers[i].m_isConnected && m_controllers[i].m_controllerID == instance) {
			return i;
		}
	}
	return -1;
}


//::.. HELP FUNCTIONS ..:://
void PlayerController::Init()
{
	SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);

	for (size_t i = 0; i < NUM_BUTTONS; i++)
	{
		m_button[i].isDown = false;
		m_button[i].isHeld = false;
		m_button[i].isUp = false;
	}

	for (size_t i = 0; i < NUM_AXIS; i++)
	{
		m_axis[i].axisDeadzone = 0;
		m_axis[i].axisRaw = 0;
	}

	m_deadzone = 0.3f;
}


void PlayerController::ButtonDown(const SDL_ControllerButtonEvent controllerEvent)
{	
	switch (controllerEvent.button)
	{
	case SDL_CONTROLLER_BUTTON_A:
		m_button[CONTROLLER_BUTTON_A].isDown = true;
		m_button[CONTROLLER_BUTTON_A].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_B:
		m_button[CONTROLLER_BUTTON_B].isHeld = true;
		m_button[CONTROLLER_BUTTON_B].isDown = true;
		break;

	case SDL_CONTROLLER_BUTTON_X:
		m_button[CONTROLLER_BUTTON_X].isDown = true;
		m_button[CONTROLLER_BUTTON_X].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_Y:
		m_button[CONTROLLER_BUTTON_Y].isDown = true;
		m_button[CONTROLLER_BUTTON_Y].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_BACK:
		m_button[CONTROLLER_BUTTON_BACK].isDown = true;
		m_button[CONTROLLER_BUTTON_BACK].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_START:
		m_button[CONTROLLER_BUTTON_START].isDown = true;
		m_button[CONTROLLER_BUTTON_START].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
		m_button[CONTROLLER_BUTTON_LEFTBUTTON].isDown = true;
		m_button[CONTROLLER_BUTTON_LEFTBUTTON].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		m_button[CONTROLLER_BUTTON_RIGHTBUTTON].isDown = true;
		m_button[CONTROLLER_BUTTON_RIGHTBUTTON].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_DPAD_UP:
		m_button[CONTROLLER_BUTTON_DPAD_UP].isDown = true;
		m_button[CONTROLLER_BUTTON_DPAD_UP].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
		m_button[CONTROLLER_BUTTON_DPAD_DOWN].isDown = true;
		m_button[CONTROLLER_BUTTON_DPAD_DOWN].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		m_button[CONTROLLER_BUTTON_DPAD_LEFT].isDown = true;
		m_button[CONTROLLER_BUTTON_DPAD_LEFT].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
		m_button[CONTROLLER_BUTTON_DPAD_RIGHT].isDown = true;
		m_button[CONTROLLER_BUTTON_DPAD_RIGHT].isHeld = true;
		break;

	}
}

void PlayerController::ButtonUp(const SDL_ControllerButtonEvent controllerEvent)
{
	switch (controllerEvent.button)
	{
	case SDL_CONTROLLER_BUTTON_A:
		m_button[CONTROLLER_BUTTON_A].isUp = true;
		m_button[CONTROLLER_BUTTON_A].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_B:
		m_button[CONTROLLER_BUTTON_B].isUp = true;
		m_button[CONTROLLER_BUTTON_B].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_X:
		m_button[CONTROLLER_BUTTON_X].isUp = true;
		m_button[CONTROLLER_BUTTON_X].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_Y:
		m_button[CONTROLLER_BUTTON_Y].isUp = true;
		m_button[CONTROLLER_BUTTON_Y].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_BACK:
		m_button[CONTROLLER_BUTTON_BACK].isUp = true;
		m_button[CONTROLLER_BUTTON_BACK].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_START:
		m_button[CONTROLLER_BUTTON_START].isUp = true;
		m_button[CONTROLLER_BUTTON_START].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
		m_button[CONTROLLER_BUTTON_LEFTBUTTON].isUp = true;
		m_button[CONTROLLER_BUTTON_LEFTBUTTON].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		m_button[CONTROLLER_BUTTON_RIGHTBUTTON].isUp = true;
		m_button[CONTROLLER_BUTTON_RIGHTBUTTON].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_DPAD_UP:
		m_button[CONTROLLER_BUTTON_DPAD_UP].isUp = true;
		m_button[CONTROLLER_BUTTON_DPAD_UP].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
		m_button[CONTROLLER_BUTTON_DPAD_DOWN].isUp = true;
		m_button[CONTROLLER_BUTTON_DPAD_DOWN].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		m_button[CONTROLLER_BUTTON_DPAD_LEFT].isUp = true;
		m_button[CONTROLLER_BUTTON_DPAD_LEFT].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
		m_button[CONTROLLER_BUTTON_DPAD_RIGHT].isUp = true;
		m_button[CONTROLLER_BUTTON_DPAD_RIGHT].isHeld = false;
		break;

	}
}

void PlayerController::GetAxis(const SDL_ControllerAxisEvent controllerEvent)
{

	switch (controllerEvent.axis) {

		// Left Stick
		// Horizonal
	case SDL_CONTROLLER_AXIS_LEFTX:
		if (ScaleRange(controllerEvent.value) > m_deadzone || ScaleRange(controllerEvent.value) < -m_deadzone)
		{
			m_axis[CONTROLLER_AXIS_LEFT_X].axisDeadzone = ScaleRange(controllerEvent.value);
		}
		else
		{
			m_axis[CONTROLLER_AXIS_LEFT_X].axisDeadzone = 0.0f;
		}
		break;

		// Vetical
	case SDL_CONTROLLER_AXIS_LEFTY:
		if (ScaleRange(controllerEvent.value) > m_deadzone || ScaleRange(controllerEvent.value) < -m_deadzone)
		{
			m_axis[CONTROLLER_AXIS_LEFT_Y].axisDeadzone = ScaleRange(controllerEvent.value);
		}
		else
		{
			m_axis[CONTROLLER_AXIS_LEFT_Y].axisDeadzone = 0.0f;
		}
		break;


		// Right stick
		// Horizontal
	case SDL_CONTROLLER_AXIS_RIGHTX:
		if (ScaleRange(controllerEvent.value) > m_deadzone || ScaleRange(controllerEvent.value) < -m_deadzone)
		{
			m_axis[CONTROLLER_AXIS_RIGHT_X].axisDeadzone = ScaleRange(controllerEvent.value);
		}
		else
		{
			m_axis[CONTROLLER_AXIS_RIGHT_X].axisDeadzone = 0.0f;
		}
		break;
		// Vetical
	case SDL_CONTROLLER_AXIS_RIGHTY:
		if (ScaleRange(controllerEvent.value) > m_deadzone || ScaleRange(controllerEvent.value) < -m_deadzone)
		{
			m_axis[CONTROLLER_AXIS_RIGHT_Y].axisDeadzone = ScaleRange(controllerEvent.value);
		}
		else
		{
			m_axis[CONTROLLER_AXIS_RIGHT_Y].axisDeadzone = 0.0f;
		}
		break;

		// Left trigger
	case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
		if (ScaleRange(controllerEvent.value) > m_deadzone)
		{
			m_axis[CONTROLLER_AXIS_TRIGGERLEFT].axisDeadzone = ScaleRange(controllerEvent.value);
		}
		else
		{
			m_axis[CONTROLLER_AXIS_TRIGGERLEFT].axisDeadzone = 0.0f;
		}
		break;

		// Right trigger
	case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
		if (ScaleRange(controllerEvent.value) > m_deadzone)
		{
			m_axis[CONTROLLER_AXIS_TRIGGERRIGHT].axisDeadzone = ScaleRange(controllerEvent.value);
		}
		else
		{
			m_axis[CONTROLLER_AXIS_TRIGGERRIGHT].axisDeadzone = 0.0f;
		}
		break;
	}
}

void PlayerController::GetAxisRaw(const SDL_ControllerAxisEvent controllerEvent)
{
	switch (controllerEvent.axis) {

		// Left Stick
		// Horizonal
	case SDL_CONTROLLER_AXIS_LEFTX:
		m_axis[CONTROLLER_AXIS_LEFT_X].axisRaw = ScaleRange(controllerEvent.value);
		break;

		// Vetical
	case SDL_CONTROLLER_AXIS_LEFTY:
		m_axis[CONTROLLER_AXIS_LEFT_Y].axisRaw = ScaleRange(controllerEvent.value);
		break;

		// Right stick
		// Horizontal
	case SDL_CONTROLLER_AXIS_RIGHTX:
		m_axis[CONTROLLER_AXIS_RIGHT_X].axisRaw = ScaleRange(controllerEvent.value);
		break;
		// Vetical
	case SDL_CONTROLLER_AXIS_RIGHTY:
		m_axis[CONTROLLER_AXIS_RIGHT_Y].axisRaw = ScaleRange(controllerEvent.value);
		break;

		// Left trigger
	case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
		m_axis[CONTROLLER_AXIS_TRIGGERLEFT].axisRaw = ScaleRange(controllerEvent.value);
		break;

		// Right trigger
	case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
		m_axis[CONTROLLER_AXIS_TRIGGERRIGHT].axisRaw = ScaleRange(controllerEvent.value);
		break;
	}
}

//Scale range to [-1, 1]
float PlayerController::ScaleRange(Sint16 value)
{

	float result = (2.0f * ((value - (-32768.0f)) / (32767.0f - (-32768.0f))) - 1.0f);

	return result;
}