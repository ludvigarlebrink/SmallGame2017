#ifndef __ANTIALIASING_H__
#define __ANTIALIASING_H__

#include <glew.h>
#include <iostream>

class AntiAliasing
{
public:
	AntiAliasing();
	virtual ~AntiAliasing();

	void Init();


	//::.. HELPER FUNCTIONS ..:://
	GLuint GenerateMultiSampleTexture(GLuint samples);

	void Update();
private:
private:
	GLuint m_framebuffer;
	GLuint m_rbo;
	GLuint m_textureColorBufferMultiSampled;
	//GLuint m_texture;
};

#endif // !__ANTIALIASING_H__
