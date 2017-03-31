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
