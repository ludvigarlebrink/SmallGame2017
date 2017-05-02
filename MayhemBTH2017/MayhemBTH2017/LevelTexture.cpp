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



}

bool LevelTexture::SaveImage(std::string fileName)
{

	glReadBuffer(GL_FRONT);
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
	return true;



}


