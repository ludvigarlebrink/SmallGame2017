#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__


#include "Scene.h"


#include <cstdint>


class LevelManager
{
public:
	LevelManager();
	virtual ~LevelManager();

	void StartUp();
	void ShutDown();

	void Update();

	bool LoadNextScene();
	bool LoadSceneAtIndex(uint32_t index);
	bool LoadScene();
	
private:
	static LevelManager * m_instance;


};


#endif