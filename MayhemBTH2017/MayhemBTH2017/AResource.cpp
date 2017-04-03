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
	m_filePath = original.GetFilePath();
	m_fileName = original.GetFilePath();
}

AResource::~AResource()
{
}

std::string AResource::GetFilePath()const
{
	return m_filePath;
}

std::string AResource::GetFileName()const
{
	return m_fileName;
}
