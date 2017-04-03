#include "PlayerController.h"



PlayerController::PlayerController()
{
	// Do nothing...
}


PlayerController::~PlayerController()
{
	// Do nothing...
}

void PlayerController::StartUp()
{
	Init();
}

void PlayerController::ShutDown()
{
	//Shutdown
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
			ButtonInput(m_event.cbutton);
			break;

		case SDL_CONTROLLERAXISMOTION:
			AxisInput(m_event.caxis);
			break;
		}
	}
}

void PlayerController::Init()
{
	SDL_Init(SDL_INIT_GAMECONTROLLER);
}

void PlayerController::AddPlayerController(SDL_ControllerDeviceEvent PlayerControllerID)
{
	if (SDL_IsGameController(PlayerControllerID.which))
	{
		SDL_GameController * m_controller = SDL_GameControllerOpen(PlayerControllerID.which);
		std::cout << "Controller added!: " << PlayerControllerID.which << std::endl;
	}
}

void PlayerController::RemovePlayerController()
{
	SDL_GameControllerClose(m_controller);
	std::cout << "Controller removed!: " << m_controller << std::endl;
}

void PlayerController::ButtonInput(const SDL_ControllerButtonEvent controllerEvent)
{
	switch (controllerEvent.button)
	{
	case SDL_CONTROLLER_BUTTON_A:
		tempCounter += 1;
		std::cout << "Pressed A! tempCounter: " << tempCounter << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_B:
		tempCounter += 1;
		std::cout << "Pressed B! tempCounter: " << tempCounter << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_X:
		tempCounter += 1;
		std::cout << "Pressed X! tempCounter: " << tempCounter << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_Y:
		tempCounter += 1;
		std::cout << "Pressed Y! tempCounter: " << tempCounter << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_BACK:
		tempCounter += 1;
		std::cout << "Pressed BACK! tempCounter: " << tempCounter << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_START:
		tempCounter += 1;
		std::cout << "Pressed START! tempCounter: " << tempCounter << std::endl;
		break;

	}
}

void PlayerController::AxisInput(const SDL_ControllerAxisEvent controllerEvent)
{
	switch (controllerEvent.axis)
	{
	case SDL_CONTROLLER_AXIS_LEFTX:
		tempCounter += 1;
		std::cout << "AXIS_LEFTX" << tempCounter << std::endl;
		break;

	case SDL_CONTROLLER_AXIS_LEFTY:
		tempCounter += 1;
		std::cout << "AXIS_LEFTY" << tempCounter << std::endl;
		break;

	case SDL_CONTROLLER_AXIS_RIGHTX:
		tempCounter += 1;
		std::cout << "AXIS_RIGHTX" << tempCounter << std::endl;
		break;

	case SDL_CONTROLLER_AXIS_RIGHTY:
		tempCounter += 1;
		std::cout << "AXIS_RIGHTY" << tempCounter << std::endl;
		break;
	}
}
