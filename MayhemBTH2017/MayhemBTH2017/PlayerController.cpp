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
		std::cout << "Pressed A!" << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_B:
		std::cout << "Pressed B!" << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_X:
		std::cout << "Pressed X!" << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_Y:
		std::cout << "Pressed Y!" << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_BACK:
		std::cout << "Pressed BACK!" << std::endl;
		break;

	case SDL_CONTROLLER_BUTTON_START:
		std::cout << "Pressed START!" << std::endl;
		break;

	}
}

void PlayerController::AxisInput(const SDL_ControllerAxisEvent controllerEvent)
{

	switch (controllerEvent.axis)
	{
		//Left Stick
	case SDL_CONTROLLER_AXIS_LEFTX:
		if (controllerEvent.value > 2500 || controllerEvent.value < -2500)
			std::cout << "AXIS_LEFTX Value: " << controllerEvent.value << std::endl;
		break;

	case SDL_CONTROLLER_AXIS_LEFTY:
		if (controllerEvent.value > 1500 || controllerEvent.value < -1500)
			std::cout << "AXIS_LEFTY Value: " << controllerEvent.value << std::endl;
		break;

		//Right Stick
	case SDL_CONTROLLER_AXIS_RIGHTX:
		if (controllerEvent.value > 3500 || controllerEvent.value < -3500)
			std::cout << "AXIS_RIGHTX Value: " << controllerEvent.value << std::endl;
		break;

	case SDL_CONTROLLER_AXIS_RIGHTY:
		if (controllerEvent.value > 3500 || controllerEvent.value < -3500)
			std::cout << "AXIS_RIGHTY Value: " << controllerEvent.value << std::endl;
		break;
	}
}
