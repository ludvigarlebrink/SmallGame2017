#include "LevelHandler.h"


//::.. CONSTRUCTORS ..:://
LevelHandler::LevelHandler()
	: m_regHasChanged(false), m_noneIsLoaded(true)
{
	// Do nothing...
}


LevelHandler::~LevelHandler()
{
	// Do nothing...
}


void LevelHandler::Init()
{

	//Name max size 16
	//std::string maxSizeofString = "MAX 16 TECKEN!!!";
	//m_size = maxSizeofString.size();
	m_size = 4;
	char* nameBuffer = new char[m_size];
	
	std::ifstream file(".\\Assets\\Levels\\NewFormat.mrlevel", std::ios::binary);
	//Read header!
	//1. nr of maps
	//2. map names
	file.read(reinterpret_cast<char*>(m_nrOfMaps), sizeof(uint32_t));
	for (int i = 0; i < m_nrOfMaps[0]; i++)
	{
		file.read(reinterpret_cast<char*>(nameBuffer), m_size);
		nameBuffer[m_size] = '\0';
		m_names[i] = nameBuffer;
		std::cout << m_names[i] << " : " << m_nrOfMaps[0] << std::endl;
	}

	file.close();

}

//::.. IMPORT/EXPORT ..:://
void LevelHandler::Import(Level & level, uint32_t id)
{


	uint32_t headerSize = sizeof(uint32_t) + m_size + id;
	const int nrOfBlocks = level.SIZE_X * level.SIZE_Y;

	bool isOccupied[nrOfBlocks] = { 0 };
	bool isSpawn[nrOfBlocks] = { 0 };
	glm::vec2 *uv = new glm::vec2[nrOfBlocks];
	glm::vec2 *uv2 = new  glm::vec2[nrOfBlocks * (12 * 2)];
	glm::vec3 *rgb = new glm::vec3[(nrOfBlocks * 6) * 3];

	uint32_t i = 0;
	
	m_mapSize = sizeof(isOccupied) + sizeof(isSpawn) + sizeof(uv) + sizeof(uv2) + sizeof(rgb);
	
	std::ifstream file(".\\Assets\\Levels\\NewFormat.mrlevel", std::ios::binary);
	file.ignore(sizeof(uint32_t));
	for (int i = 0; i < m_nrOfMaps[0]; i++)
	{
		file.ignore(m_size);
	}
	//file.ignore(headerSize);
	//file.ignore(m_mapSize * id);
	file.read(reinterpret_cast<char*>(isOccupied), sizeof(bool) * nrOfBlocks);
	file.read(reinterpret_cast<char*>(isSpawn), sizeof(bool) * nrOfBlocks);
	file.read(reinterpret_cast<char*>(uv), sizeof(glm::vec2) * nrOfBlocks);
	file.read(reinterpret_cast<char*>(uv2), sizeof(uint32_t) * (nrOfBlocks * 12) * 2);
	file.read(reinterpret_cast<char*>(rgb), sizeof(uint32_t) * (nrOfBlocks * 6) * 3);


	for (size_t x = 1; x < level.SIZE_X; x++)
	{
		for (size_t y = 1; y < level.SIZE_Y; y++)
		{
			level.SetOccupied(x, y, isOccupied[i]);
			level.SetSpawnPoint(x, y, isSpawn[i]);
			if(isOccupied[i])
				level.AddBlock(x, y,uv[i]);
	

			i++;
		}
	}

	file.close();



}


void LevelHandler::Export(Level & level)
{
	LevelRegister newRegister;
	newRegister.isLoaded = true;
	newRegister.name = level.GetName();
	newRegister.level = nullptr;
	m_register.push_back(newRegister);

	char* nameBuffer = new char[m_size];
	std::ifstream input(".\\Assets\\Levels\\NewFormat.mrlevel", std::ios::binary);
	//Read header!
	//1. nr of maps
	//2. map names
	input.read(reinterpret_cast<char*>(m_nrOfMaps), sizeof(uint32_t));
	std::cout << m_nrOfMaps[0] << std::endl;
	for (int i = 0; i < m_nrOfMaps[0]; i++)
	{
		input.read(reinterpret_cast<char*>(nameBuffer), m_size);
		nameBuffer[m_size] = '\0';
		m_names[i] = nameBuffer;
	}
	input.close();


	const int nrOfBlocks = level.SIZE_X * level.SIZE_Y;
	bool isOccupied[nrOfBlocks] = { 0 };
	bool isSpawn[nrOfBlocks] = { 0 };
	glm::vec2 uvCoords[nrOfBlocks] = {glm::vec2(0,0)};
	uint32_t i = 0;
	for (size_t x = 1; x < level.SIZE_X; x++)
	{
		for (size_t y = 1; y < level.SIZE_Y; y++)
		{
			isOccupied[i] = level.GetIsOccupied(x, y);
			isSpawn[i] = level.GetIsSpawnPoint(x, y);
			uvCoords[i] = level.GetTempUV(x, y);
			i++;
		}
	}

	std::ofstream output(".\\Assets\\Levels\\NewFormat.mrlevel", std::ios::binary);
	output.write(reinterpret_cast<char*>(m_nrOfMaps), sizeof(uint32_t));
	for (uint32_t x = 0; x < m_nrOfMaps[0]; x++)
	{
		output.write(reinterpret_cast<char*>(const_cast<char*>(&m_names[x].c_str()[0])), (m_size));
	}
	output.write(reinterpret_cast<char*>(isOccupied), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	output.write(reinterpret_cast<char*>(isSpawn), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	output.write(reinterpret_cast<char*>(uvCoords), sizeof(glm::vec2) * (level.SIZE_X * level.SIZE_Y));
	output.close();

}


bool LevelHandler::ImportRegister()
{
	// Try to open the file.
	std::ifstream file(".\\Assets\\Levels\\Register.mrlevelreg", std::ios::binary);

	// Check if the file is open.
	if (!file.is_open())
	{
		return false;
	}

	// Check version.
	uint32_t version = 0;
	file.read(reinterpret_cast<char*>(&version), sizeof(uint32_t));

	// Version not supported.
	if (version < 1)
	{
		return false;
	}
	
	// Clear the current register.
	m_register.clear();

	// Check number of levels;
	uint32_t numLevels = 0;
	file.read(reinterpret_cast<char*>(&numLevels), sizeof(uint32_t));

	// Resize to fit the levels.
	m_register.resize(numLevels);

	// Loop through the level cache and read from file.
	for (uint32_t i = 0; i < numLevels; i++)
	{
		// Size of the file string.
		uint32_t stringSize = static_cast<uint32_t>(m_register[i].name.size());
		file.read(reinterpret_cast<char*>(&stringSize), sizeof(uint32_t));

		// The acual string.
		const char * string = m_register[i].name.c_str();
		file.read(reinterpret_cast<char*>(&string), sizeof(char) * stringSize);

		// Add to the register.
		m_register[i].name = string;
		m_register[i].level = nullptr;
	}

	// Close the file.
	file.close();

	return true;
}


bool LevelHandler::ExportRegister()
{
	// Check if there is anything to export.
	if (m_register.empty())
	{
		return false;
	}

	// Open the file.
	std::ofstream file(".\\Assets\\Levels\\Register.mrlevelreg", std::ios::binary);

	// Version.
	uint32_t version = 1;
	file.write(reinterpret_cast<char*>(&version), sizeof(uint32_t));

	// Number of levels.
	uint32_t numLevels = static_cast<uint32_t>(m_register.size());
	file.write(reinterpret_cast<char*>(&numLevels), sizeof(uint32_t));

	// Loop through the level cache and write to file.
	for (uint32_t i = 0; i < numLevels; i++)
	{
		// Size of the file string.
		uint32_t stringSize = static_cast<uint32_t>(m_register[i].name.length());

		std::cout << stringSize << std::endl;
		file.write(reinterpret_cast<char*>(&stringSize), sizeof(uint32_t));

		// Loop through the string and store each char in the file.
		for (uint32_t j = 0; j < stringSize; j++)
		{
			char c = m_register[i].name[j];
			file.write(reinterpret_cast<char*>(&c), sizeof(char));
		}
	}

	// Close the file.
	file.close();
	
	return true;
}


//::.. MODIFY FUNCTIONS ..:://
bool LevelHandler::AddToRegister(Level * level)
{
	return false;
}


uint32_t LevelHandler::GetNumLevels()
{
	return m_register.size();
}


//::.. GET FUNCTIONS ..:://
uint32_t LevelHandler::GetMaxNumLevels()
{
	return uint32_t();
}


Level * LevelHandler::GetLoadedLevel()
{
	if (m_noneIsLoaded)
	{
		return nullptr;
	}

	return m_register[m_loaded].level;
}