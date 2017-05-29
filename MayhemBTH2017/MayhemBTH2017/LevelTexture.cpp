#include "LevelTexture.h"



LevelTexture::LevelTexture()
{
}


LevelTexture::~LevelTexture()
{
}

void LevelTexture::Init()
{

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
	std::ofstream file(fileName.c_str(), std::ios::binary);


	unsigned char TGAheader[12] = { 0,0,1,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6] = { m_width % 256, m_width / 256, 
		m_height % 256, m_height / 256, 24,0};
	
	file.write(reinterpret_cast<char*>(TGAheader), sizeof(unsigned char) * 12);
	file.write(reinterpret_cast<char*>(header), sizeof(unsigned char) * 6);
	file.write(reinterpret_cast<char*>(m_dataBuffer), sizeof(GLubyte) * nSize);
	file.close();

	free(m_dataBuffer);

	return true;
}

void LevelTexture::SetStatus(bool save)
{
	m_saveNextFrame = save;
}

bool LevelTexture::GetStatus()
{
	return m_saveNextFrame;
}


