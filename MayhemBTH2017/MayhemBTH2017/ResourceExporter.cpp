#include "ResourceExporter.h"



ResourceExporter::ResourceExporter()
{
	m_filepath = ".\\Assets\\ResourceRegister.mrregister";
}


ResourceExporter::~ResourceExporter()
{
}

bool ResourceExporter::Export(Resource * resource)
{
	if (resource == nullptr)
	{
		return false;
	}

	m_resource = resource;

	// Open the file.
	m_file.open(m_filepath, std::ios::binary);

	// Write version.
	uint32_t version = VERSION;
	m_file.write(reinterpret_cast<char*>(&version), sizeof(uint32_t));
	

	ExportLevels();

	m_file.close();

	return true;
}

bool ResourceExporter::ExportLevels()
{
	// Number of levels.
	

	// 

	return false;
}