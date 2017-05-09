#ifndef __LEVELHANDLER_H__
#define __LEVELHANDLER_H__


#include "Level.h"
#include "LevelEditorPropPlacer.h"
#include "UIText.h"


#include <fstream>
#include <vector>
#include <experimental/filesystem>

class LevelHandler
{
public:

	struct PropsImport
	{
		uint32_t	id;
		glm::vec2	pos;
		float		rot;
	};

	LevelHandler();
	virtual ~LevelHandler();

	//::.. IMPORT/EXPORT ..:://
	void Init();
	void Import(Level & level, uint32_t id, std::string levelName);
	void Export(Level & level, LevelEditorPropPlacer & propPlacer);
	bool ImportRegister(std::string & textField);
	bool ExportRegister();
	bool TestImportRegister();
	bool TestExportRegister();
	



	//::.. MODIFY FUNCTIONS ..:://
	bool AddToRegister(Level * level);
	bool RemoveFromRegister(const char* name);
	bool RemoveFromRegisterAt(uint32_t index);
	bool FindInRegister(const char* name);

	//::.. GET FUNCTIONS ..:://
	//uint32_t	GetNumLevels();
	uint32_t	GetMaxNumLevels();
	Level *		GetLoadedLevel();
	uint32_t	ReadNumLevels();
	std::string ReadLevel(std::string levelName);
	uint32_t	GetNumLevels();
	void		GetLevelNames(std::vector<std::string> & strVec);

	//::.. SET FUNCTIONS ..:://
	void IncrementNumLevels();

private:
	struct LevelRegister
	{
		bool			isLoaded;
		std::string		name;
		Level*			level;
	};

	bool								m_noneIsLoaded;
	bool								m_regHasChanged;
	std::vector<LevelRegister>			m_register;
	std::vector<std::string>			m_levelNames;
	uint32_t							m_loaded;

private:
	uint32_t							m_nrOfMaps[1];
	std::string							m_names[3];
	uint32_t							m_size;
	uint32_t							m_mapSize;
	uint32_t							m_width = 84;
	uint32_t							m_height = 48;
	uint32_t							m_numLevels = 0;
	uint32_t							numLevels;
	LevelEditorPropPlacer::PropsExport* outProps;
};

#endif // ! __LEVELIMPORTER_H__