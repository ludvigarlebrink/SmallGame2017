#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

bool Scene::Load()
{
	// LOAD FROM FILE
	return false;
}

bool Scene::Clear()
{
	m_gameObjects.Clear();
	return true;
}

void Scene::Update()
{
}

void Scene::Render()
{
}

void Scene::AddGameObject()
{
}

void Scene::AddGameObject(uint32_t parentID)
{
}


//::.. HELP FUNCTIONS ..:://
void Scene::Traverse()
{
}
