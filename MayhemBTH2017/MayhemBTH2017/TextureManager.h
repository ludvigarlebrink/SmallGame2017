#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__


#include <MrMatHandler.h>
#include <SDL.h>
#include <map>
#include <glew.h>


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

	//::.. MODIFY FUNCTIONS ..:://
	static void AddTexture(const char * name, const char* filepath);
	static GLuint AddTexture(MrTexture * texture);
	static GLuint Load(MrTexture * texture);
	static void FreeTexture(GLuint id);
	static void FreeTexture(const char * name);
	static void DeleteTextureFromMap(const char * name);

	//::.. GET FUNCTIONS ..:://
	static TextureManager Get();
	static Texture GetTexture(const char * name);
	static GLuint GetTextureID(const char * name);

private:
	static std::map<std::string, Texture> m_textureArray;
	static TextureManager * m_instance;


};

#endif // !__TEXTUREMANAGER_H__