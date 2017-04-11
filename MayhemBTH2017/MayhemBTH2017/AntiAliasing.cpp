#include "AntiAliasing.h"


//::.. DUMMY CONSTRUCTORS ..:://
AntiAliasing::AntiAliasing()
{
	this->Init();
}


AntiAliasing::~AntiAliasing()
{
}

//::.. HELPER FUNCTIONS ..:://
GLuint AntiAliasing::GenerateMultiSampleTexture(GLuint samples)
{
	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, 1280, 720, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	return texture;
}

GLuint AntiAliasing::GenerateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
	GLenum attachment_type;
	if (!depth && !stencil)
		attachment_type = GL_RGB;
	else if (depth && !stencil)
		attachment_type = GL_DEPTH_COMPONENT;
	else if (!depth && stencil)
		attachment_type = GL_STENCIL_INDEX;

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	if (!depth && !stencil)
		glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, 1280, 720, 0, attachment_type,
			GL_UNSIGNED_BYTE, NULL);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 1280, 720, 0, GL_DEPTH_STENCIL,
			GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}


void AntiAliasing::Init()
{
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	m_textureColorBufferMultiSampled = GenerateMultiSampleTexture(4);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_textureColorBufferMultiSampled, 0);
	
	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, 1280, 720);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

#ifdef _DEBUG

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "FRAMEBUFFER MSAA ERROR\n";
	}
#endif
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Second FBO

	m_screenTexture = GenerateAttachmentTexture(false, false);
	glGenFramebuffers(1, &m_intermediateFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_intermediateFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_screenTexture, 0);
#ifdef _DEBUG

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "FRAMEBUFFER MSAA ERROR\n";
	}
#endif
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void AntiAliasing::Update()
{

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_intermediateFBO);
	glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1280, 720, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
}

void AntiAliasing::Bind()
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_screenTexture);
}

void AntiAliasing::Reset()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}