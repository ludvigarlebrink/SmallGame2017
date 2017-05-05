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
	bool GetButtonDown(size_t button, size_t controller = 0);
	bool GetButtonHeld(size_t button, size_t controller = 0);
	bool GetButtonUp(size_t button, size_t controller = 0);
	float GetAxis(size_t axis, size_t controller = 0);
	float GetAxisRaw(size_t axis, size_t controller = 0);
	int GetControllerID(int ID);

	//::.. MODIFY FUNCTIONS ..:://
	void Update();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	uint32_t m_nrOfPlayers, m_maxNrOfPlayers;
	static InputManager*	m_instance;
	PlayerController		m_playerController[1];

};

#endif
