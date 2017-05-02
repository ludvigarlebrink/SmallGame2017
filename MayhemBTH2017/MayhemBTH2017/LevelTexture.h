#ifndef __LEVELTEXTURE_H__
#define __LEVELTEXTURE_H__

#include <string>
#include <glew.h>
#include <iostream>

class LevelTexture
{
public:
	LevelTexture();
	virtual ~LevelTexture();
	void Init();
	bool SaveImage(std::string fileName);

private:
	char*	m_dataBuffer;
	//temp
	int		m_width = 32;
	int		m_height = 32;
	int		m_nrOfMaps;


	GLuint	m_frameBuffer;
};

#endif // !__LEVELTEXTURE_H__
