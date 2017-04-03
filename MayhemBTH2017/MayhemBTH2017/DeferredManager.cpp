#include "DeferredManager.h"

//::.. DUMMY CONSTRUCTORS ..:://

DeferredManager::DeferredManager()
{
}


DeferredManager::~DeferredManager()
{
}


//::.. FAKE FUNCTIONS ..:://

void DeferredManager::StartUp()
{
	{
		if (m_instance == nullptr)
		{
			Init();
		}
	}
}

void DeferredManager::ShutDown()
{
	//NOTHING BRAH!
}

void DeferredManager::Init()
{
	CreateBuffers();
}

void DeferredManager::CreateBuffers()
{
	glGenFramebuffers(1, &m_gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_gBuffer);

	//Framebuffer for positions
	glGenTextures(1, &m_gPosition);
	glBindTexture(GL_TEXTURE_2D, m_gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, M_SCR_WIDTH, M_SCR_HEIGHT, 0,
		GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		m_gPosition, 0);

	//Framebuffer for positions
	glGenTextures(1, &m_gNormals);
	glBindTexture(GL_TEXTURE_2D, m_gNormals);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, M_SCR_WIDTH, M_SCR_HEIGHT, 0,
		GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
		m_gNormals, 0);

	//Framebuffer for normals and specular
	glGenTextures(1, &m_gColorSpecular);
	glBindTexture(GL_TEXTURE_2D, m_gColorSpecular);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, M_SCR_WIDTH, M_SCR_HEIGHT, 0,
		GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
		m_gColorSpecular, 0);

	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	
	glGenRenderbuffers(1, &m_rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, M_SCR_WIDTH, M_SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
		m_rboDepth);

#ifdef _DEBUG

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "FRAMEBUFFER NOT COMPLETE---------- \n";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

#endif


}

void DeferredManager::BindBuffers()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_gBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DeferredManager::BindTextures()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_gNormals);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_gColorSpecular);
}

void DeferredManager::CopyBuffer()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_gBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, M_SCR_WIDTH, M_SCR_HEIGHT, 0, 0,
		M_SCR_WIDTH, M_SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

}

//::.. GET FUNCTIONS ..:://

GLuint DeferredManager::GetPositionsMap()const
{
	return m_gPosition;
}

GLuint DeferredManager::GetNormalMap()const
{
	return m_gNormals;
}

GLuint DeferredManager::GetColorSpec()const
{
	return m_gColorSpecular;
}

Vector<glm::vec3> DeferredManager::GetLightPos()const
{
	return this->m_lightPosition;
}

Vector<glm::vec3> DeferredManager::GetLightColor()const
{
	return this->m_lightColor;
}