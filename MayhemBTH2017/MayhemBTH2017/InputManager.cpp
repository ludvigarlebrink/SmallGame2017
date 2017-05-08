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
	return m_playerController->GetButtonDown(button, controller);
}

bool InputManager::GetButtonHeld(size_t button, size_t controller)
{
	return m_playerController->GetButtonHeld(button, controller);
}

bool InputManager::GetButtonUp(size_t button, size_t controller)
{
	return m_playerController->GetButtonUp(button, controller);
}

float InputManager::GetAxis(size_t axis, size_t controller)
{
	return m_playerController->GetAxis(axis, controller);
}

float InputManager::GetAxisRaw(size_t axis, size_t controller)
{
	return m_playerController->GetAxisRaw(axis, controller);
}

int InputManager::GetControllerID(int ID)
{
	return m_playerController->GetControllerIndex(ID);
}


PlayerController * InputManager::GetController()
{
	return &m_playerController[0];
}

void InputManager::Update()
{
	m_playerController[0].Reset();
	m_playerController[0].Update();
}

void InputManager::Init()
{
	m_nrOfPlayers = 1;
	m_maxNrOfPlayers = 4;

	std::cout << "INITTED" << std::endl;
}

void InputManager::ShutDown()
{
	// Do something...
}
