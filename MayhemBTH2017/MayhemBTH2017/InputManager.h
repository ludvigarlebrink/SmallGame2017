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
	bool GetButtonDown(size_t button, size_t controller = 0);
	bool GetButtonHeld(size_t button, size_t controller = 0);
	bool GetButtonUp(size_t button, size_t controller = 0);

	//::.. SET FUNCTIONS ..:://
	void SetNrOfPlayers(uint32_t value);

	//::.. MODIFY FUNCTIONS ..:://
	void AddPlayer();
	void RemovePlayer(uint32_t value);
	void Update();
	void Reset();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	uint32_t m_nrOfPlayers, m_maxNrOfPlayers;
	static InputManager* m_instance;
	PlayerController	 m_playerController[4];
};

#endif
