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


	//int nSize = m_width * m_height * 3;
	uint32_t i = 0;
	uint32_t propSize = 0;

	std::ifstream file(".\\Assets\\Levels\\NewFormat.mrlevel", std::ios::binary);

	file.read(reinterpret_cast<char*>(isOccupied), sizeof(bool) * nrOfBlocks);
	file.read(reinterpret_cast<char*>(isSpawn), sizeof(bool) * nrOfBlocks);
	file.read(reinterpret_cast<char*>(uv), sizeof(glm::vec2) * nrOfBlocks);
	file.ignore(sizeof(unsigned char) * (m_height * m_width) * 4);
	file.read(reinterpret_cast<char*>(&propSize), sizeof(uint32_t));
	std::cout << propSize << std::endl;

	PropsImport * importedProps = new PropsImport[propSize];
	for (uint32_t i = 0; i < propSize; i++)
	{
		file.read(reinterpret_cast<char*>(&importedProps[i].id), sizeof(uint32_t));
		file.read(reinterpret_cast<char*>(&importedProps[i].pos), sizeof(glm::vec2));
		file.read(reinterpret_cast<char*>(&importedProps[i].rot), sizeof(float));
	
	}


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
	delete[] importedProps;
}


void LevelHandler::Export(Level & level, LevelEditorPropPlacer & propPlacer)
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
	
	outProps = propPlacer.GetPropExport();
	uint32_t propsSize = propPlacer.GetNumProps();

	char* nameBuffer = new char[m_size];
	
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
			++i;
		}
	}
	/*uint8_t * texData = new uint8_t[level.SIZE_X * level.SIZE_Y * 4];
	uint32_t counter = 0;

	for (uint32_t i = 0; i < level.SIZE_X * level.SIZE_Y * 4; i += 4)
	{
		if (isOccupied[counter])
		{
			switch (static_cast<int>(uvCoords[counter].x))
			{
			case 0:
				texData[i] = 199;
				texData[i + 1] = 198;
				texData[i + 2] = 198;
				texData[i + 3] = 255;

				break;
			case 1:
				texData[i] = 103;
				texData[i + 1] = 165;
				texData[i + 2] = 197;
				texData[i + 3] = 255;

				break;
			case 2:
				texData[i] = 58;
				texData[i + 1] = 145;
				texData[i + 2] = 84;
				texData[i + 3] = 255;

				break;
			case 3:
				texData[i] = 251;
				texData[i + 1] = 180;
				texData[i + 2] = 242;
				texData[i + 3] = 255;

				break;
			case 4:
				texData[i] = 90;
				texData[i + 1] = 99;
				texData[i + 2] = 109;
				texData[i + 3] = 255;

				break;
			case 5:
				texData[i] = 230;
				texData[i + 1] = 197;
				texData[i + 2] = 157;
				texData[i + 3] = 255;

				break;
			case 6:
				texData[i] = 176;
				texData[i + 1] = 175;
				texData[i + 2] = 175;
				texData[i + 3] = 255;

				break;
			case 7:
				texData[i] = 198;
				texData[i + 1] = 137;
				texData[i + 2] = 191;
				texData[i + 3] = 255;

				break;
			case 8:
				texData[i] = 1;
				texData[i + 1] = 1;
				texData[i + 2] = 1;
				texData[i + 3] = 1;

				break;
			case 9:
				texData[i] = 2;
				texData[i + 1] = 2;
				texData[i + 2] = 2;
				texData[i + 3] = 2;

				break;
			case 10:
				texData[i] = 3;
				texData[i + 1] =3;
				texData[i + 2] =3;
				texData[i + 3] =3;

				break;
			case 11:
				texData[i] = 4;
				texData[i + 1] = 4;
				texData[i + 2] = 4;
				texData[i + 3] = 4;

				break;
			case 13:
				texData[i] = 5;
				texData[i + 1] = 5;
				texData[i + 2] = 5;
				texData[i + 3] = 5;

				break;
			case 14:
				texData[i] = 6;
				texData[i + 1] = 6;
				texData[i + 2] = 6;
				texData[i + 3] = 6;

				break;
			case 15:
				texData[i] = 7;
				texData[i + 1] = 7;
				texData[i + 2] = 7;
				texData[i + 3] = 7;

				break;
			default:
				break;
			}
		}
		else
		{
			texData[i] = 8;
			texData[i + 1] = 8;
			texData[i + 2] = 8;
			texData[i + 3] = 8;
		}
		++counter;
	}*/
	int x = 2;

	std::ofstream output(".\\Assets\\Levels\\NewFormat.mrlevel", std::ios::binary);

	output.write(reinterpret_cast<char*>(isOccupied), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	output.write(reinterpret_cast<char*>(isSpawn), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	output.write(reinterpret_cast<char*>(uvCoords), sizeof(glm::vec2) * (level.SIZE_X * level.SIZE_Y));
	// TEST:


	//output.write(reinterpret_cast<char*>(texData), sizeof(uint8_t) * (level.SIZE_X * level.SIZE_Y) * 4);
	output.write(reinterpret_cast<char*>(tempPixelBuffer), sizeof(unsigned char) *(m_height * m_width) * 4);
	output.write(reinterpret_cast<char*>(&propsSize), sizeof(uint32_t));
	for (uint32_t i = 0; i < 2; i++)
	{
		output.write(reinterpret_cast<char*>(&outProps[i].id), sizeof(uint32_t));
		output.write(reinterpret_cast<char*>(&outProps[i].pos), sizeof(glm::vec2));
		output.write(reinterpret_cast<char*>(&outProps[i].rot), sizeof(float));

	}



	/*for (size_t i = 0; i < 84 * 48 * 4; i += 4)
	{
		std::cout << i<<"\t "<< "R: " << (int)tempPixelBuffer[i];
		std::cout << "\tG: " << (int)tempPixelBuffer[i + 1];
		std::cout << "\tB: " << (int)tempPixelBuffer[i + 2];
		std::cout << "\tA: " << (int)tempPixelBuffer[i + 3] << std::endl;

	}*/
	std::cout << "saved" << std::endl;
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