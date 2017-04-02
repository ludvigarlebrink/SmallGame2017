#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__


#include "Scene.h"


#include <cstdint>


class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void StartUp();
	void ShutDown();

	void Update();

	bool LoadNextScene();
	bool LoadSceneAtIndex(uint32_t index);
	bool LoadScene();
	
private:
	static SceneManager * m_instance;


};


#endif