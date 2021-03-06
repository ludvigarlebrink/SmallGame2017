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
	for (uint32_t i = 0; i < m_nrOfMaps[0]; i++)
	{
		file.read(reinterpret_cast<char*>(nameBuffer), m_size);
		nameBuffer[m_size] = '\0';
		m_names[i] = nameBuffer;
	}

	file.close();

}

//::.. IMPORT/EXPORT ..:://
void LevelHandler::Import(Level & level, std::string levelName)
{
	level.Clear();
	const int nrOfBlocks = level.SIZE_X * level.SIZE_Y;

	bool isOccupied[nrOfBlocks] = { 0 };
	bool isSpawn[nrOfBlocks] = { 0 };
	glm::vec2 * uv = new glm::vec2[nrOfBlocks];

	//int nSize = m_width * m_height * 3;
	uint32_t i = 0;
	uint32_t propSize = 0;

	std::ifstream file(".\\Assets\\Levels\\" + levelName + ".mrlevel", std::ios::binary);

	file.read(reinterpret_cast<char*>(isOccupied), sizeof(bool) * nrOfBlocks);
	file.read(reinterpret_cast<char*>(uv), sizeof(glm::vec2) * nrOfBlocks);
//	file.ignore(sizeof(unsigned char) * (m_height * m_width) * 4);

	for (uint32_t x = 1; x < level.SIZE_X; x++)
	{
		for (uint32_t y = 1; y < level.SIZE_Y; y++)
		{
			level.SetOccupied(x, y, isOccupied[i]);

			if (level.GetIsOccupied(x, y))
			{
				level.RemoveBlock(x, y);
				level.AddBlock(x, y, uv[i]);
			}

			i++;
		}
	}

	file.close();

	delete uv;
}


void LevelHandler::Export(Level & level)
{
	LevelRegister newRegister;
	newRegister.isLoaded = true;
	newRegister.name = level.GetName();
	newRegister.level = nullptr;
	m_register.push_back(newRegister);

	int nSize = m_width * m_height * 4;


	glReadBuffer(GL_FRONT);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	unsigned char* tempPixelBuffer;
	tempPixelBuffer = new unsigned char[m_height * m_width * 4];
	glReadPixels(0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, tempPixelBuffer);

	char* nameBuffer = new char[m_size];

	const int nrOfBlocks = level.SIZE_X * level.SIZE_Y;
	bool isOccupied[nrOfBlocks] = { 0 };
	bool isSpawn[nrOfBlocks] = { 0 };

	//glm::vec2 uvCoords[nrOfBlocks] = { glm::vec2(4,0) };
	glm::vec2 * uvCoords = new glm::vec2[nrOfBlocks];

	uint32_t i = 0;
	for (uint32_t x = 1; x < level.SIZE_X; x++)
	{
		for (uint32_t y = 1; y < level.SIZE_Y; y++)
		{
			isOccupied[i] = level.GetIsOccupied(x, y);
			uvCoords[i] = level.GetTempUV(x, y);			

			++i;
		}
	}

	std::ofstream output(".\\Assets\\Levels\\" + level.GetName() + ".mrlevel", std::ios::binary);

	output.write(reinterpret_cast<char*>(isOccupied), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	output.write(reinterpret_cast<char*>(uvCoords), sizeof(glm::vec2) * (level.SIZE_X * level.SIZE_Y));
	// TEST:


	//output.write(reinterpret_cast<char*>(texData), sizeof(uint8_t) * (level.SIZE_X * level.SIZE_Y) * 4);
	//output.write(reinterpret_cast<char*>(tempPixelBuffer), sizeof(unsigned char) *(m_height * m_width) * 4);

	output.close();

	delete uvCoords;


}


bool LevelHandler::ImportRegister(std::string & textField)
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
	//m_register.clear();

	// Check number of levels;
	uint32_t numLevels = static_cast<uint32_t>(m_register.size());
	file.read(reinterpret_cast<char*>(&numLevels), sizeof(uint32_t));

	// Resize to fit the levels.
	m_register.resize(numLevels);

	// Loop through the level cache and read from file.
	for (uint32_t i = 0; i < numLevels; i++)
	{
		// Size of the file string.
		uint32_t stringSize = static_cast<uint32_t>(m_register[i].name.length());
		file.read(reinterpret_cast<char*>(&stringSize), sizeof(uint32_t));

		// The acual string.
		for (uint32_t j = 0; j < stringSize; j++)
		{
			char string = m_register[i].name[j];
			file.read(reinterpret_cast<char*>(&string), sizeof(char));
			m_register[i].name.push_back(string);

		}
		// Add to the register.
		/*m_register[i].name = string;
		m_register[i].level = nullptr;*/

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
	std::ofstream file(".\\Assets\\Levels\\Register.mrlevelreg", std::ios::binary | std::ios::app);

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

bool LevelHandler::TestImportRegister()
{
	// Open the file.
	std::ifstream file(".\\Assets\\Levels\\Register.mrlevelreg", std::ios::binary);

	// Check if the file is open.
	if (!file.is_open())
	{
		return false;
	}

	file.read(reinterpret_cast<char*>(&m_numLevels), sizeof(uint32_t));


	// Close the file.
	file.close();

	return true;
}

bool LevelHandler::TestExportRegister()
{

	if (ReadNumLevels() + 1 <= 0)
		return false;
	else
		m_numLevels = ReadNumLevels() + 1;

	// Open the file.
	std::ofstream file(".\\Assets\\Levels\\Register.mrlevelreg", std::ios::binary);

	// Check if the file is open.
	if (!file.is_open())
	{
		return false;
	}

	// Update file with new number of levels.
	file.write(reinterpret_cast<char*>(&m_numLevels), sizeof(uint32_t));

	for (uint32_t i = 0; i < m_numLevels; i++)
	{
		file.write(reinterpret_cast<char*>(&m_numLevels), sizeof(uint32_t));
	}

	// Close the file.
	file.close();

	return true;
}

uint32_t LevelHandler::ReadNumLevels()
{
	std::ifstream file(".\\Assets\\Levels\\Register.mrlevelreg", std::ios::binary);

	// Check if the file is open.
	if (!file.is_open())
	{
		return -1;
	}

	file.read(reinterpret_cast<char*>(&m_numLevels), sizeof(uint32_t));

	// Close the file.
	file.close();

	return m_numLevels;
}

uint32_t LevelHandler::GetNumLevels()
{
	numLevels = 0;
	std::string path = ".\\Assets\\Levels\\";
	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		numLevels++;
	}

	return numLevels;
}

void LevelHandler::GetLevelNames(std::vector<std::string> & strVec)
{
	std::string path = ".\\Assets\\Levels\\";
	size_t firstChar = path.find_last_of("\\");
	size_t lastChar = path.find_last_of(".");
	std::string temp;
	std::string temp2;
	strVec.clear();
	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		temp = p.path().string();
		temp2 = temp.substr(firstChar + 1, temp.length());
		strVec.push_back(temp2.substr(0, temp2.find_last_of(".")));
	}
}

void LevelHandler::IncrementNumLevels()
{
	++numLevels;
}



//::.. MODIFY FUNCTIONS ..:://
bool LevelHandler::AddToRegister(Level * level)
{
	return false;
}

bool LevelHandler::RemoveFromRegister(const char * name)
{
	return false;
}

bool LevelHandler::RemoveFromRegisterAt(uint32_t index)
{
	return false;
}

bool LevelHandler::FindInRegister(const char * name)
{
	return false;
}


//uint32_t LevelHandler::GetNumLevels()
//{
//	return m_register.size();
//}


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