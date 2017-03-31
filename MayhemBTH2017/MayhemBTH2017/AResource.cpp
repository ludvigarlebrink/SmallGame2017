#include "AResource.h"



AResource::AResource()
	:m_filePath(""), m_fileName("")
{
	// Init.
}

AResource::AResource(std::string & filePath, std::string & fileName)
{
	m_filePath = filePath;
	m_fileName = fileName;

}

AResource::AResource(const AResource & original)
{
	m_filePath = original.getFilePath();
	m_fileName = original.getFilePath();

}

AResource::~AResource()
{
}

std::string AResource::getFilePath()const
{
	return m_filePath;
}

std::string AResource::getFileName()const
{
	return m_fileName;
}
