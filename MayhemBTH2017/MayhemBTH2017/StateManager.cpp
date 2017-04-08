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
void StateManager::SetCurrentState(GameState state)
{
	m_currentState = state;
}

StateManager * StateManager::Get()
{
	return m_instance;
}


//::.. GET FUNCTIONS ..:://
GameState StateManager::GetCurrentState()
{
	return m_currentState;
}

void StateManager::Init()
{
	m_currentState = GameState::START;
}
