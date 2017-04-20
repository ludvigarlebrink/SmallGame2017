#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <SDL.h>
#include <map>
#include <GL\glew.h>


class TextureManager
{
public:
	struct Texture
	{
		GLuint ID;
		GLuint width;
		GLuint height;
		GLuint numComponents;
	};

	//::.. CONSTRUCTORS ..:://
	TextureManager();
	virtual ~TextureManager();

	void StartUp();
	void Shutdown();

	//::.. OTHER FUNCTIONS ..:://
	static void AddTexture(const char * name, const char* filepath);
	static void FreeTexture(GLuint id);
	static void FreeTexture(const char * name);
	static void DeleteTextureFromMap(const char * name);

	//::.. GET FUNCTIONS ..:://
	static TextureManager Get();
	static Texture GetTexture(const char * name);
	static GLuint GetTextureID(const char * name);

private:
	static std::map<const char *, Texture> m_textureArray;
	static TextureManager * m_instance;


};

#endif // !__TEXTUREMANAGER_H__