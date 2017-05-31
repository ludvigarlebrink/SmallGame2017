#ifndef __RESOURCEEXPORTER_H__
#define	__RESOURCEEXPORTER_H__


#include "Resource.h"


#include <cstdint>
#include <fstream>



class ResourceExporter
{
public:
	ResourceExporter();
	virtual ~ResourceExporter();

	bool Export(Resource * resource);

private:
	bool ExportLevels();
	bool ExportPlaylist();
	bool ExportMesh();

private:
	const uint32_t	VERSION = 1;

	const char*		m_filepath;
	std::ofstream	m_file;
	Resource *		m_resource;
};


#endif // ! __RESOURCEEXPORTER_H__