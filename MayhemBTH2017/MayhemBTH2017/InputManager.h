#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include "PlayerController.h"

class InputManager
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	InputManager();
	virtual ~InputManager();

	//::.. FAKE CONSTRUCTORS ..:://
	void StartUp();
	void ShutDown();

	//::.. GET FUNCTIONS ..:://
	static InputManager* Get();
	uint32_t GetNrOfPlayers();

	//::.. SET FUNCTIONS ..:://
	void SetNrOfPlayers(uint32_t value);

	//::.. MODIFY FUNCTIONS ..:://
	void AddPlayer();
	void RemovePlayer(uint32_t value);
	void Update();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	uint32_t m_nrOfPlayers, m_maxNrOfPlayers;
	static InputManager* m_instance;
	PlayerController	 m_playerController[4];
};

#endif
