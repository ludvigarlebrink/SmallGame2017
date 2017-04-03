#ifndef __SCENE_H__
#define __SCENE_H__


#include "AGameObject.h"
#include "Vector.h"


class Scene
{
public:
	Scene();
	virtual ~Scene();

	bool Load();		// Returns false if file is not found.
	bool Clear();

	void Update();
	void Render();

	//::.. MODIFY FUNCTIONS ..:://
	void AddGameObject();
	void AddGameObject(uint32_t parentID);

private:
	//::.. HELP FUNCTIONS ..:://
	void Traverse();

private:
	// Camera
	Vector<AGameObject> m_gameObjects;
	
};


#endif