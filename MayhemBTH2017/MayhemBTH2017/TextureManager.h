#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include "Textures.h"
#include "ImageLoader.h"
#include <string.h>

class TextureManager
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	TextureManager();
	virtual ~TextureManager();

	//::.. FAKE FUNCTIONS ..:://
	void StartUp();
	void ShutDown();

	//::.. GET FUNCTIONS ..:://
	static TextureManager* Get();

	//::.. SET FUNCTIONS ..:://

	//::.. HELPER FUNCTIONS ..:://
	void AddTexture(GLuint id, const std::string& filePath);
	void bindTexture(GLuint id);

private:
	void Init();
private:
	static TextureManager * m_instance;
	//Textures m_texture;
	//ImageLoader m_imageLoader;


};

#endif // !__TEXTUREMANAGER_H__
