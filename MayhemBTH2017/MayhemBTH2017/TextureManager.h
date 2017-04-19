#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <SDL.h>
#include <map>
#include <GL\glew.h>


class TextureManager
{
public:
	//::..Constructor, Destructor..:://
	TextureManager();
	virtual ~TextureManager();

	GLuint GetTextureID(std::string name);

	void AddTexture(std::string name, const char* filepath);



private:
	std::map<std::string, GLuint> m_textureIDArray;


};

#endif // !__TEXTUREMANAGER_H__