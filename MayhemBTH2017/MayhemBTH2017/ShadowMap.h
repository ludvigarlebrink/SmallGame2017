#ifndef __SHADOWMAP_H__
#define __SHADOWMAP_H__


#include <glew.h>
#include <string>

class ShadowMap
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	ShadowMap();
	virtual ~ShadowMap();

	//::.. HELPER FUNCTIONS ..:://
	void Init();
	void FirstPass();
	void SecPass();
	void Bind();

	//::.. GET FUNCTIONS ..:://
	GLuint GetMap()const;



private:
	const GLuint SHADOW_WIDTH = 1920, SHADOW_HEIGHT = 1080;
	GLuint m_depthMap;
	GLuint m_depthMapFBO;
};

#endif // !__SHADOWMAP_H__
