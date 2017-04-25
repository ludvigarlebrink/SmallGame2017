#include "Level.h"



Level::Level()
{
	Init();
	m_name = "New_Level";
	m_input = InputManager::Get();
}


Level::~Level()
{

}

void Level::Render(Camera camera)
{
	// SELECT THE SHADER
	// UPDATE THE SHADER

	Transform tran;

	m_debugShader.Bind();

	m_debugShader.Update(tran, camera);


	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{

		m_uv.x = (32 * 3) / 512.0;
		m_uv.y = 0.0 / 512.0;
		m_uv.z = 32 / 512.0;
		m_uv.w = 32 / 512.0;
		std::cout << "pressed" << std::endl;
	}

	//Left stick
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		m_uv.x = 0.0/ 512.0;
		m_uv.y = 0.0 / 512.0;
		m_uv.z = 512.0 / 512.0;
		m_uv.w = 512.0 / 512.0;

	}

	m_debugShader.SendTexture(0, "t", m_uv);

	m_mesh.Render();

	m_mesh2.Render();
}


//::.. MODIFY FUNCTIONS ..:://
void Level::AddBlock(uint32_t posX, uint32_t posY)
{
	if (!m_grid[posX][posY].isOccupied)
	{
		SetOccupied(posX, posY, true);
	}

	UpdateBlocks(posX, posY, true);
	m_mesh.Update(); //Front quad
	m_mesh2.Update(); //Z-quad

}

void Level::RemoveBlock(uint32_t posX, uint32_t posY)
{
	if (m_grid[posX][posY].isOccupied)
	{
		SetOccupied(posX, posY, false);
	}

	UpdateBlocks(posX, posY, false);
	m_mesh.Update(); //Front quad
	m_mesh2.Update(); //Z-quad
}

void Level::AddSpawnPoint(uint32_t posX, uint32_t posY)
{
	if (!GetIsOccupied(posX, posY))
	{
		SetSpawnPoint(posX, posY, !GetIsSpawnPoint(posX, posY));
	}
}


//::.. GET FUNCTIONS ..:://
bool Level::GetIsOccupied(uint32_t posX, uint32_t posY)
{
	return m_grid[posX][posY].isOccupied;
}

bool Level::GetIsSpawnPoint(uint32_t posX, uint32_t posY)
{
	return m_grid[posX][posY].isSpawnPoint;
}

uint32_t Level::GetTextureID(uint32_t posX, uint32_t posY)
{
	return m_grid[posX][posY].textureID;
}

const std::string & Level::GetName()
{
	return m_name;
}


//::.. SET FUNCTIONS ..:://
void Level::SetTexture(uint32_t posX, uint32_t posY, uint32_t textureID)
{
	m_grid[posX][posY].textureID = textureID;
}

void Level::SetOccupied(uint32_t posX, uint32_t posY, bool isOccupied)
{
	m_grid[posX][posY].isOccupied = isOccupied;
}

void Level::SetSpawnPoint(uint32_t posX, uint32_t posY, bool isSpawnPoint)
{
	m_grid[posX][posY].isSpawnPoint = isSpawnPoint;
}

void Level::SetName(const std::string & name)
{
	m_name = name;
}


//::.. HELP FUNCTIONS ..:://
void Level::Init()
{
	//m_debugShader.Init("DebugShader", false, 0);
	m_debugShader.Init(".\\Assets\\GLSL\\LevelShader", false, false);
	InitGrid();
	InitMesh();
}

void Level::InitGrid()
{
	for (size_t x = 0; x < SIZE_X; x++)
	{
		for (size_t y = 0; y < SIZE_Y; y++)
		{
			m_grid[x][y].textureID = 0;
			m_grid[x][y].isOccupied = false;
			m_grid[x][y].isSpawnPoint = false;
		}
	}
}

void Level::InitMesh()
{
	const uint64_t length = SIZE_X * SIZE_Y * 6;
	const uint64_t length2 = SIZE_X * SIZE_Y * 12;
	m_vertices = (Vertex3D*)malloc(sizeof(Vertex3D) * length);
	m_vertices2 = (Vertex3D*)malloc(sizeof(Vertex3D) * length2);

	uint64_t i = 0;

	float scaler = 1.0f;

	for (uint64_t x = 0; x < SIZE_X; x++)
	{
		for (uint64_t y = 0; y < SIZE_Y; y++)
		{
			// Quad 1.
			m_vertices[i].position = glm::vec3((x + 0.5f), (y + 0.5f), -2.0f * scaler);
			m_vertices[i].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i].texCoordsAlpha = glm::vec3(0.0f, 0.0f, 0.0f);

			m_vertices[i + 1].position = glm::vec3((x + 0.5f), (y - 0.5f), -2.0f * scaler);
			m_vertices[i + 1].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 1].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices[i + 2].position = glm::vec3((x - 0.5f), (y + 0.5f), -2.0f * scaler);
			m_vertices[i + 2].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 2].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices[i + 3].position = glm::vec3((x - 0.5f), (y + 0.5f), -2.0f * scaler);
			m_vertices[i + 3].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 3].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices[i + 4].position = glm::vec3((x + 0.5f), (y - 0.5f), -2.0f * scaler);
			m_vertices[i + 4].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 4].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices[i + 5].position = glm::vec3((x - 0.5f), (y - 0.5f), -2.0f * scaler);
			m_vertices[i + 5].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 5].texCoordsAlpha = glm::vec3(1.0f, 1.0f, 0.0f);
			i += 6;
		
		}
	}

	i = 0;

	for (uint64_t x = 0; x < SIZE_X; x++)
	{
		for (uint64_t y = 0; y < SIZE_Y; y++)
		{
			// Quad 2.
			m_vertices2[i].position = glm::vec3(x + 0.5f, y + 0.5f, 2.0f);
			m_vertices2[i].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i].texCoordsAlpha = glm::vec3(0.0f, 0.0f, 0.0f);

			m_vertices2[i + 1].position = glm::vec3(x + 0.5f, y + 0.5f, -2.0f);
			m_vertices2[i + 1].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 1].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices2[i + 2].position = glm::vec3(x - 0.5f, y + 0.5f, -2.0f);
			m_vertices2[i + 2].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 2].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices2[i + 3].position = glm::vec3(x - 0.5f, (y + 0.5f), 2.0f);
			m_vertices2[i + 3].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 3].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices2[i + 4].position = glm::vec3(x + 0.5f, y + 0.5f, 2.0f);
			m_vertices2[i + 4].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 4].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices2[i + 5].position = glm::vec3(x - 0.5f, y + 0.5f, -2.0f);
			m_vertices2[i + 5].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 5].texCoordsAlpha = glm::vec3(1.0f, 1.0f, 0.0f);

			// Quad 3.
			m_vertices2[i + 6].position = glm::vec3(x + 0.5f, y + 0.5f, 2.0f);
			m_vertices2[i + 6].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 6].texCoordsAlpha = glm::vec3(0.0f, 0.0f, 0.0f);

			m_vertices2[i + 7].position = glm::vec3(x + 0.5f, y - 0.5f, -2.0f);
			m_vertices2[i + 7].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 7].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices2[i + 8].position = glm::vec3(x + 0.5f, y + 0.5f, -2.0f);
			m_vertices2[i + 8].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 8].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices2[i + 9].position = glm::vec3(x + 0.5f, y + 0.5f, 2.0f);
			m_vertices2[i + 9].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 9].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices2[i + 10].position = glm::vec3(x + 0.5f, y - 0.5f, 2.0f);
			m_vertices2[i + 10].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 10].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices2[i + 11].position = glm::vec3(x + 0.5f, y - 0.5f, -2.0f);
			m_vertices2[i + 11].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 11].texCoordsAlpha = glm::vec3(1.0f, 1.0f, 0.0f);

			i += 12;
		}
	}


	m_mesh.Load(m_vertices, length);
	m_mesh2.Load(m_vertices2, length2);
}

void Level::UpdateBlocks(uint32_t posX, uint32_t posY, bool isOccupied)
{


	

	uint64_t pos = (posY + (posX * SIZE_Y)) * 6;
	for (size_t i = 0; i < 6; i++)
	{
		if (isOccupied)
		{
			m_vertices[pos + i].texCoordsAlpha = glm::vec3(m_vertices[i].texCoordsAlpha.x,
				m_vertices[pos + i].texCoordsAlpha.y, 1.0f);
		}
		else
		{
			m_vertices[pos + i].texCoordsAlpha = glm::vec3(m_vertices[i].texCoordsAlpha.x,
				m_vertices[pos + i].texCoordsAlpha.y, 0.0f);
		}
	}

	pos = (posY + (posX * SIZE_Y)) * 12;

	for (size_t i = 0; i < 12; i++)
	{
		if (isOccupied)
		{
			m_vertices2[pos + i].texCoordsAlpha = glm::vec3(m_vertices[i].texCoordsAlpha.x,
				m_vertices2[pos + i].texCoordsAlpha.y, 1.0f);
		}
		else
		{
			m_vertices2[pos + i].texCoordsAlpha = glm::vec3(m_vertices[i].texCoordsAlpha.x,
				m_vertices2[pos + i].texCoordsAlpha.y, 0.0f);
		}
	}


	pos = (posY - 1 + (posX * SIZE_Y)) * 12;

	if (pos < 0)
	{
		std::cout << "RETURN!" << std::endl;
		return;
	}

	for (size_t i = 0; i < 6; i++)
	{
		if (isOccupied)
		{
			m_vertices2[pos + i].texCoordsAlpha = glm::vec3(m_vertices[i].texCoordsAlpha.x,
				m_vertices2[pos + i].texCoordsAlpha.y, 1.0f);
		}
		else
		{
			m_vertices2[pos + i].texCoordsAlpha = glm::vec3(m_vertices[i].texCoordsAlpha.x,
				m_vertices2[pos + i].texCoordsAlpha.y, 0.0f);
		}
	}

	pos = (posY - SIZE_Y + (posX * SIZE_Y)) * 12;
	


	for (size_t i = 6; i < 12; i++)
	{
		if (isOccupied)
		{
			m_vertices2[pos + i].texCoordsAlpha = glm::vec3(m_vertices[i].texCoordsAlpha.x,
				m_vertices2[pos + i].texCoordsAlpha.y, 1.0f);
		}
		else
		{
			m_vertices2[pos + i].texCoordsAlpha = glm::vec3(m_vertices[i].texCoordsAlpha.x,
				m_vertices2[pos + i].texCoordsAlpha.y, 0.0f);
		}
	}

}
