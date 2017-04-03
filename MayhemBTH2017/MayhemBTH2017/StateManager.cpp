#include "StateManager.h"



StateManager * StateManager::m_instance = nullptr;


//::.. DUMMY CONSTRUCTORS ..:://
StateManager::StateManager()
{
	// Do nothing...
}


StateManager::~StateManager()
{
	// Do nothing...
}


//::.. FAKE CONSTRUCTORS ..:://
void StateManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
		Init();
	}
}

void StateManager::ShutDown()
{
	// Clear shit...
}


//::.. SET FUNCTIONS ..:://
void StateManager::SetCurrentState(State state)
{
}

StateManager * StateManager::Get()
{
	return m_instance;
}


//::.. GET FUNCTIONS ..:://
StateManager::State StateManager::GetCurrentState()
{
	return m_currentState;
}

void StateManager::Init()
{
	m_currentState = State::START;
}
