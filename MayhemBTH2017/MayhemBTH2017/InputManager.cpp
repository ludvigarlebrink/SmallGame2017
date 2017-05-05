#include "InputManager.h"



InputManager * InputManager::m_instance = nullptr;


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
		m_instance = this;
		Init();
	}
}

InputManager * InputManager::Get()
{
	return m_instance;
}


bool InputManager::GetButtonDown(size_t button, size_t controller)
{
	return m_playerController[controller].GetButtonDown(button);
}

bool InputManager::GetButtonHeld(size_t button, size_t controller)
{
	return m_playerController[controller].GetButtonHeld(button);
}

bool InputManager::GetButtonUp(size_t button, size_t controller)
{
	return m_playerController[controller].GetButtonUp(button);
}

float InputManager::GetAxis(size_t axis, size_t controller)
{
	return m_playerController[controller].GetAxis(axis);
}

float InputManager::GetAxisRaw(size_t axis, size_t controller)
{
	return m_playerController[controller].GetAxisRaw(axis);
}

void InputManager::Update()
{

	m_playerController[0].Update();

}

void InputManager::Init()
{
	m_nrOfPlayers = 1;
	m_maxNrOfPlayers = 4;

	SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);
	std::cout << "INITTED" << std::endl;
}

void InputManager::ShutDown()
{
	// Do something...
}
