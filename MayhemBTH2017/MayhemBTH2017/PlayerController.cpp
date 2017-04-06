#include "PlayerController.h"



PlayerController::PlayerController()
{
	Init();
}


PlayerController::~PlayerController()
{
	// Do nothing...
}

void PlayerController::Update()
{
	while (SDL_PollEvent(&m_event) != 0)
	{
		switch (m_event.type)
		{
		case SDL_CONTROLLERDEVICEADDED:
			AddPlayerController(m_event.cdevice);
			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			RemovePlayerController();
			break;

		case SDL_CONTROLLERBUTTONDOWN:
			ButtonDown(m_event.cbutton);
			break;

		case SDL_CONTROLLERBUTTONUP:
			ButtonUp(m_event.cbutton);
			break;

		case SDL_CONTROLLERAXISMOTION:
			AxisInput(m_event.caxis);
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

void PlayerController::AddPlayerController(SDL_ControllerDeviceEvent PlayerControllerID)
{
	if (SDL_IsGameController(PlayerControllerID.which))
	{
		SDL_GameController * m_controller = SDL_GameControllerOpen(PlayerControllerID.which);
	}
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

float PlayerController::GetAxisDirection(size_t button)
{
	return m_button[button].axisDirection;
}

size_t PlayerController::GetNumButtons()
{
	return NUM_BUTTONS;
}


//::.. HELP FUNCTIONS ..:://
void PlayerController::Init()
{
	for (size_t i = 0; i < NUM_BUTTONS; i++)
	{
		m_button[i].isDown = false;
		m_button[i].isHeld = false;
		m_button[i].isUp = false;
		m_button[i].axisDirection = 0;
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
		m_button[CONTROLLER_BUTTON_LEFTSHOULDER].isDown = true;
		m_button[CONTROLLER_BUTTON_LEFTSHOULDER].isHeld = true;
		break;

	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		m_button[CONTROLLER_BUTTON_RIGHTSHOULDER].isDown = true;
		m_button[CONTROLLER_BUTTON_RIGHTSHOULDER].isHeld = true;
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
		m_button[CONTROLLER_BUTTON_LEFTSHOULDER].isUp = true;
		m_button[CONTROLLER_BUTTON_LEFTSHOULDER].isHeld = false;
		break;

	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		m_button[CONTROLLER_BUTTON_RIGHTSHOULDER].isUp = true;
		m_button[CONTROLLER_BUTTON_RIGHTSHOULDER].isHeld = false;
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

void PlayerController::AxisInput(const SDL_ControllerAxisEvent controllerEvent)
{

	switch (controllerEvent.axis)
	{

		//Left Stick
		//Horizonal
	case SDL_CONTROLLER_AXIS_LEFTX:
		if (ScaleRange(controllerEvent.value) > m_deadzone || ScaleRange(controllerEvent.value) < -m_deadzone)
		{
			m_button[CONTROLLER_AXIS_LEFTX].isHeld = true;
			m_button[CONTROLLER_AXIS_LEFTX].isDown = true;
			m_button[CONTROLLER_AXIS_LEFTX].axisDirection = ScaleRange(controllerEvent.value);

			if (m_button[CONTROLLER_AXIS_LEFTX].axisDirection > m_deadzone)
			{
				m_button[CONTROLLER_AXIS_LEFTX].axisDirection = 1.0f;
			}

			if (m_button[CONTROLLER_AXIS_LEFTX].axisDirection < -m_deadzone)
			{
				m_button[CONTROLLER_AXIS_LEFTX].axisDirection = -1.0f;
			}
		}
		else
		{
			m_button[CONTROLLER_AXIS_LEFTX].isHeld = false;
			m_button[CONTROLLER_AXIS_LEFTX].isDown = false;
			m_button[CONTROLLER_AXIS_LEFTX].axisDirection = 0.0f;
		}
		break;
		//Vetical
	case SDL_CONTROLLER_AXIS_LEFTY:
		if (ScaleRange(controllerEvent.value) > m_deadzone || ScaleRange(controllerEvent.value) < -m_deadzone)
		{
			m_button[CONTROLLER_AXIS_LEFTY].isHeld = true;
			m_button[CONTROLLER_AXIS_LEFTY].isDown = true;
			m_button[CONTROLLER_AXIS_LEFTY].axisDirection = ScaleRange(controllerEvent.value);

			if (m_button[CONTROLLER_AXIS_LEFTY].axisDirection > m_deadzone)
			{
				m_button[CONTROLLER_AXIS_LEFTY].axisDirection = 1.0f;
			}

			if (m_button[CONTROLLER_AXIS_LEFTY].axisDirection < -m_deadzone)
			{
				m_button[CONTROLLER_AXIS_LEFTY].axisDirection = -1.0f;
			}
		}
		else
		{
			m_button[CONTROLLER_AXIS_LEFTY].isHeld = false;
			m_button[CONTROLLER_AXIS_LEFTY].isDown = false;
			m_button[CONTROLLER_AXIS_LEFTY].axisDirection = 0.0f;
		}
		break;


		//Right stick
		//Horizontal
	case SDL_CONTROLLER_AXIS_RIGHTX:
		if (ScaleRange(controllerEvent.value) > m_deadzone || ScaleRange(controllerEvent.value) < -m_deadzone)
		{
			m_button[CONTROLLER_AXIS_RIGHTX].isHeld = true;
			m_button[CONTROLLER_AXIS_RIGHTX].isDown = true;
			m_button[CONTROLLER_AXIS_RIGHTX].axisDirection = ScaleRange(controllerEvent.value);

			if (m_button[CONTROLLER_AXIS_RIGHTX].axisDirection > m_deadzone)
			{
				m_button[CONTROLLER_AXIS_RIGHTX].axisDirection = 1.0f;
			}

			if (m_button[CONTROLLER_AXIS_RIGHTX].axisDirection < -m_deadzone)
			{
				m_button[CONTROLLER_AXIS_RIGHTX].axisDirection = -1.0f;
			}
		}
		else
		{
			m_button[CONTROLLER_AXIS_RIGHTX].isHeld = false;
			m_button[CONTROLLER_AXIS_RIGHTX].isDown = false;
			m_button[CONTROLLER_AXIS_RIGHTX].axisDirection = 0.0f;
		}
		break;

	case SDL_CONTROLLER_AXIS_RIGHTY:
		if (ScaleRange(controllerEvent.value) > m_deadzone || ScaleRange(controllerEvent.value) < -m_deadzone)
		{
			m_button[CONTROLLER_AXIS_RIGHTY].isHeld = true;
			m_button[CONTROLLER_AXIS_RIGHTY].isDown = true;
			m_button[CONTROLLER_AXIS_RIGHTY].axisDirection = ScaleRange(controllerEvent.value);

			if (m_button[CONTROLLER_AXIS_RIGHTY].axisDirection > m_deadzone)
			{
				m_button[CONTROLLER_AXIS_RIGHTY].axisDirection = 1.0f;
			}

			if (m_button[CONTROLLER_AXIS_RIGHTY].axisDirection < -m_deadzone)
			{
				m_button[CONTROLLER_AXIS_RIGHTY].axisDirection = -1.0f;
			}
		}
		else
		{
			m_button[CONTROLLER_AXIS_RIGHTY].isHeld = false;
			m_button[CONTROLLER_AXIS_RIGHTY].isDown = false;
			m_button[CONTROLLER_AXIS_RIGHTY].axisDirection = 0.0f;
		}
		break;
	}
}

float PlayerController::ScaleRange(Sint16 value)
{
	//Scale range to [-1, 1]
	float result = (2.0f * ((value - (-32768.0f)) / (32767.0f - (-32768.0f))) - 1.0f);

	return result;
}
