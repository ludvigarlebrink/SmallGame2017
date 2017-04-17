#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__


#include "Mesh.h"
#include "Texture.h"
#include "String.h"

// Resource importers.
#include "ShaderImporter.h"


class ResourceManager
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	ResourceManager();
	virtual ~ResourceManager();

	//::.. FAKE CONSTRUCTORS ..:://
	void StartUp();
	void ShutDown();

	//::.. GET FUNCTIONS ..:://
	ResourceManager& Get();
	//Texture& GetTexture(const String& filepath);
	void GetShader(const char* name);
	void GetSkeleton();
	void GetAnimation();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	static ResourceManager * m_instance;
};


#endif