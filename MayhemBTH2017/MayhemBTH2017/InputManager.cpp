#include "InputManager.h"

//temp
#include <iostream>

InputManager * InputManager::m_instance = nullptr;


//::.. DUMMY CONSTRUCTORS ..:://
InputManager::InputManager()
{
	// Do nothing...
}

InputManager::~InputManager()
{
	// Do nothing...
}


//::.. FAKE CONSTRUCTORS ..:://
void InputManager::StartUp()
{
	if (m_instance == nullptr)
	{
		Init();
	}
}

void InputManager::ShutDown()
{
	// CLEAR SHIT
}

void InputManager::Update()
{
	while (SDL_PollEvent(&m_event) != 0)
	{
		if (m_event.type = SDL_CONTROLLERBUTTONDOWN)
		{
			if (m_event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				std::cout << "A Pressed" << std::endl;
			}
		}
	}
}


//::.. GET FUNCTIONS ..:://
InputManager & InputManager::Get()
{
	return *m_instance;
}

void InputManager::GetButtonInput(Button button)
{
	switch (button)
	{
	// Face buttons
	case Button::BUTTON_A: std::cout << "BUTTON_A" << std::endl;  break;
	case Button::BUTTON_B: std::cout << "BUTTON_B" << std::endl; break;
	case Button::BUTTON_X: std::cout << "BUTTON_X" << std::endl; break;
	case Button::BUTTON_Y: std::cout << "BUTTON_Y" << std::endl; break;

	// Sticks
	case Button::RIGHT_STICK: std::cout << "RIGHT_STICK" << std::endl; break;
	case Button::LEFT_STICK: std::cout << "LEFT_STICK" << std::endl; break;
	case Button::D_PAD_UP: std::cout << "D_PAD_UP" << std::endl; break;
	case Button::D_PAD_DOWN: std::cout << "D_PAD_DOWN" << std::endl; break;
	case Button::D_PAD_LEFT: std::cout << "D_PAD_LEFT" << std::endl; break;
	case Button::D_PAD_RIGHT: std::cout << "D_PAD_RIGHT" << std::endl; break;

	// Bumpers
	case Button::RIGHT_BUMPER: std::cout << "RIGHT_BUMPER" << std::endl; break;
	case Button::LEFT_BUMPER: std::cout << "LEFT_BUMPER" << std::endl; break;

	// Triggers
	case Button::RIGHT_TRIGGER: std::cout << "RIGHT_TRIGGER" << std::endl; break;
	case Button::LEFT_TRIGGER: std::cout << "LEFT_TRIGGER" << std::endl; break;

	// Menu
	case Button::START_BUTTON: std::cout << "START_BUTTON" << std::endl; break;
	case Button::BACK_BUTTON: std::cout << "BACK_BUTTON" << std::endl; break;

	}
}


//::.. HELP FUNCTIONS ..:://
void InputManager::Init()
{
	SDL_Init(SDL_INIT_GAMECONTROLLER);

	uint8_t nrOfContollers = 0;
	for (uint8_t i = 0; SDL_NumJoysticks() > i; i++)
	{
		if (SDL_IsGameController(i) && MAX_PLAYERS > nrOfContollers)
		{
			m_controller[nrOfContollers] = SDL_GameControllerOpen(i);
			++nrOfContollers;
		}
	}

}
