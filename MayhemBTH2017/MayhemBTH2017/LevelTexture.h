#ifndef __LEVELTEXTURE_H__
#define __LEVELTEXTURE_H__

#include <string>
#include <glew.h>
#include <iostream>
#include <fstream>

class LevelTexture
{
public:
	LevelTexture();
	virtual ~LevelTexture();
	void Init();
	bool SaveImage(std::string fileName);
	void SetStatus(bool save);

	bool GetStatus();

private:
	char*	m_dataBuffer;
	//temp
	int		m_width = 84;
	int		m_height = 48;
	int		m_nrOfMaps;
	bool	m_saveNextFrame;

	GLuint	m_frameBuffer;
};

#endif // !__LEVELTEXTURE_H__
