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

	// Destructor.
	virtual ~AResource();

	//::.. GET FUNCTIONS ..:://
	std::string getFilePath()const;
	std::string getFileName()const;

	//::.. READ FUNCTIONS ..:://
	virtual bool ReadFile() const = 0;

private:

	std::string m_filePath;
	std::string m_fileName;

};






#endif

