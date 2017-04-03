#ifndef __DEFERREDMANAGER_H__
#define __DEFERREDMANAGER_H__


#include "Vector.h"

#include "glm.hpp"
#include "glew.h"
#include <iostream>


class DeferredManager
{
public:

	//::.. DUMMY CONSTRUCTORS ..:://
	DeferredManager();
	virtual ~DeferredManager();

	//::.. FAKE FUNCTIONS ..:://
	void StartUp();
	void ShutDown();

	//::.. DEFERRED FUNCTIONS ..:://

	void CreateBuffers();
	void BindBuffers();
	void BindTextures();
	void CopyBuffer();
	void RandomizeLights();

	//::.. GET FUNCTIONS ..:://
	DeferredManager& Get();

	GLuint GetPositionsMap()const;
	GLuint GetNormalMap()const;
	GLuint GetColorSpec()const;
	Vector<glm::vec3> GetLightColor()const;
	Vector<glm::vec3> GetLightPos()const;

	

private:
	//::.. HELPER FUNCTIONS ..:://
	void Init();
private:
	static DeferredManager * m_instance;
	//::.. DEFERRED MEMBERS ..:://
	GLuint m_gBuffer, m_gPosition, m_gNormals, m_gColorSpecular;
	GLuint M_SCR_WIDTH;
	GLuint M_SCR_HEIGHT;
	GLuint m_rboDepth;
	Vector<glm::vec3> m_lightColor;
	Vector<glm::vec3> m_lightPosition;
};

#endif // !__DEFERREDMANAGER_H__
