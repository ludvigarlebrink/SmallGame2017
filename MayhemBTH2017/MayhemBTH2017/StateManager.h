#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

enum class GameState
{
	START,
	LOAD_MAIN_MENU,
	MAIN_MENU,
	LEVEL_EDITOR,
	GAME,
	EXIT
};

class StateManager
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	StateManager();
	virtual ~StateManager();

	//::.. FAKE CONSTRUCTORS ..:://
	void StartUp();
	void ShutDown();

	//::.. SET FUNCTIONS ..:://
	void SetCurrentState(GameState state);

	//::.. GET FUNCTIONS ..:://
	static StateManager * Get();
	GameState GetCurrentState();

private:
	void Init();

private:
	static StateManager * m_instance;

	GameState m_currentState;

};


#endif // __ STATEMANAGER_H__