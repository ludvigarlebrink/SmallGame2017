#include "LevelTexture.h"



LevelTexture::LevelTexture()
{
}


LevelTexture::~LevelTexture()
{
}

void LevelTexture::Init()
{
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(m_frameBuffer, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		m_frameBuffer, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

bool LevelTexture::SaveImage(std::string fileName)
{
	this->Init();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_BUFFER, m_frameBuffer);
	glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, 32, 32, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glReadBuffer(m_frameBuffer);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	int nSize = m_width*m_height * 3;

	m_dataBuffer = (char*)malloc(nSize * sizeof(char));

	if (!m_dataBuffer)
		return false;

	glReadPixels(0, 0, m_width, m_height, GL_BGR, GL_UNSIGNED_BYTE, m_dataBuffer);
#pragma warning (disable : 4996)
	FILE *filePtr = fopen(fileName.c_str(), "wb");
	if (!filePtr) 
		return false;

	unsigned char TGAheader[12] = { 0,0,1,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6] = { m_width % 256, m_width / 256, 
		m_height % 256, m_height / 256, 24,0};
	
	fwrite(TGAheader, sizeof(unsigned char), 12, filePtr);
	fwrite(header, sizeof(unsigned char), 6, filePtr);

	fwrite(m_dataBuffer, sizeof(GLubyte), nSize, filePtr);
	fclose(filePtr);

	free(m_dataBuffer);
	std::cout << "SAVED TEXTURE" << std::endl;
	glBindFramebuffer(0, GL_FRAMEBUFFER);
	return true;



}


