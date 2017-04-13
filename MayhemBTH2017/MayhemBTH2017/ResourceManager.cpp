#include "ResourceManager.h"



ResourceManager * ResourceManager::m_instance = nullptr;


//::.. DUMMY CONSTRUCTORS ..:://
ResourceManager::ResourceManager()
{
	// Do nothing...
}

ResourceManager::~ResourceManager()
{
	// Do nothing...
}


//::.. FAKE CONSTRUCTORS ..:://
void ResourceManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
		Init();
	}
}

void ResourceManager::ShutDown()
{
	// FREE STUFF
}


//::.. GET FUNCTIONS ..:://
ResourceManager& ResourceManager::Get()
{
	return *m_instance;
}

//Texture& ResourceManager::GetTexture(const String& filepath)
//{
//	Texture tex;
//	return tex;
//}

void ResourceManager::GetShader(const char* name)
{

}

void ResourceManager::GetSkeleton()
{
	// RETURN SKELETON
}

void ResourceManager::GetAnimation()
{
	// RETURN ANIMATION
}

void ResourceManager::Init()
{

	// INIT STUFF
}
