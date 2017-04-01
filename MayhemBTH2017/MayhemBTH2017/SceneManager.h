#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__


class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void StartUp();
	void ShutDown();

	void Update();

	bool LoadNextScene();
	bool LoadSceneAtIndex();
	bool LoadScene();
	
private:
	static SceneManager * m_instance;
};


#endif