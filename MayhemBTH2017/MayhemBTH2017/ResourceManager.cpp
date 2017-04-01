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

Mesh& ResourceManager::GetMesh(const String& filepath)
{
	return m_meshCache.GetMesh(filepath);
}

Texture& ResourceManager::GetTexture(const String& filepath)
{
	Texture tex;
	return tex;
}

void ResourceManager::GetShader()
{
	// RETURN SHADER
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
	m_instance = this;

	// INIT STUFF
}
