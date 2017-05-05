#include "PlayerController.h"



PlayerController::PlayerController()
{
	Init();
}


PlayerController::~PlayerController()
{
	// Do nothing...
}

void PlayerController::Update(Sint32 playerControllerID)
{
	while (SDL_PollEvent(&m_event) != 0)
	{
		switch (m_event.type)
		{
			case SDL_CONTROLLERDEVICEADDED:
				AddPlayerController(m_event.cdevice.which);
				break;

			//case SDL_CONTROLLERDEVICEREMOVED:
			//	RemovePlayerController();
			//	break;

		case SDL_CONTROLLERBUTTONDOWN:
			ButtonDown(playerControllerID);
			break;

		//case SDL_CONTROLLERBUTTONUP:
		//	ButtonUp(m_event.cbutton);
		//	break;

		case SDL_CONTROLLERAXISMOTION:
			GetAxis(m_event.caxis);
			GetAxisRaw(m_event.caxis);
			break;
		}
	}
}

void PlayerController::Reset()
{
	for (size_t i = 0; i < NUM_BUTTONS; i++)
	{
		m_button[i].isDown = false;
		m_button[i].isUp = false;
	}
}

void PlayerController::AddPlayerController(Sint32 playerControllerID)
{

	SDL_GameController * m_controller = SDL_GameControllerOpen(playerControllerID);
	m_controllerID = playerControllerID;

	std::cout << "ID: " << playerControllerID << std::endl;
}

void PlayerController::RemovePlayerController()
{
	SDL_GameControllerClose(m_controller);
	m_controller = nullptr;
}


//::.. GET FUNCTIONS ..:://
bool PlayerController::GetButtonDown(size_t button)
{
	return m_button[button].isDown;
}

bool PlayerController::GetButtonHeld(size_t button)
{
	return m_button[button].isHeld;
}

bool PlayerController::GetButtonUp(size_t button)
{
	return m_button[button].isUp;
}

float PlayerController::GetAxis(size_t axis)
{
	return m_axis[axis].axisDeadzone;
}

float PlayerController::GetAxisRaw(size_t axis)
{
	return m_axis[axis].axisRaw;
}

size_t PlayerController::GetNumButtons()
{
	return NUM_BUTTONS;
}

size_t PlayerController::GetNumAxis()
{
	return NUM_AXIS;
}

Sint32 PlayerController::GetControllerID()
{
	return m_controllerID;
}


//::.. HELP FUNCTIONS ..:://
void PlayerController::Init()
{
	SDL_Init(SDL_INIT_GAMECONTROLLER);

	for (size_t i = 0; i < NUM_BUTTONS; i++)
	{
		m_button[i].isDown = false;
		m_button[i].isHeld = false;
		m_button[i].isUp = false;
	}

	m_deadzone = 0.1f;
}


void PlayerController::ButtonDown(Sint32 playerControllerID)
{

	std::cout << playerControllerID << std::endl;
	std::cout << m_controllerID << std::endl;
	/*switch (controllerEvent.button)
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

	}*/
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