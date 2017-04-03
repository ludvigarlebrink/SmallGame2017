#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__


#include "MeshCache.h"
#include "TextureCache.h"
#include "ShaderCache.h"
#include "Mesh.h"
#include "Texture.h"
#include "String.h"


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
	Mesh& GetMesh(const String& filepath);
	Texture& GetTexture(const String& filepath);
	void GetShader();
	void GetSkeleton();
	void GetAnimation();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	static ResourceManager * m_instance;

	//::.. CACHES ..:://
	MeshCache		m_meshCache;
	TextureCache	m_textureCache;
	ShaderCache		m_shaderCache;

	//::.. MEMORY POOLS ..:://

};


#endif