#ifndef __ARESOURCE_H__
#define __ARESOURCE_H__

#include <string>
#include <fstream>

class AResource
{
public:
	//::.. CONSTRUCTORS ..:://
	AResource();
	AResource(std::string& filePath, std::string& fileName);
	AResource(const AResource & original);

	virtual ~AResource(); 	// Destructor

	//::.. GET FUNCTIONS ..:://
	std::string GetFilePath() const;
	std::string GetFileName() const;

	//::.. READ FUNCTIONS ..:://
	virtual bool LoadResource() const = 0;

private:
	std::string m_filePath;
	std::string m_fileName;

};


#endif // __ARESOURCE_H__

