#include "Level.h"



Level::Level()
{
	Init();
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

	m_mesh.Render();
	m_mesh2.Render();
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

void Level::AddBlock(uint32_t posX, uint32_t posY)
{
	if (!m_grid[posX][posY].isOccupied)
	{
		SetOccupied(posX, posY, !GetIsOccupied(posX, posY));
	}

	UpdateIsOccupied(posX, posY, true);
	m_mesh.Update();
	m_mesh2.Update();
}

void Level::RemoveBlock(uint32_t posX, uint32_t posY)
{
	if (!m_grid[posX][posY].isOccupied)
	{
		SetOccupied(posX, posY, !GetIsOccupied(posX, posY));
	}

	UpdateIsOccupied(posX, posY, false);
	m_mesh.Update();
	m_mesh2.Update();
}

void Level::AddSpawnPoint(uint32_t posX, uint32_t posY)
{
	if (!GetIsOccupied(posX, posY))
	{
		SetSpawnPoint(posX, posY, !GetIsSpawnPoint(posX, posY));
	}
}


//::.. HELP FUNCTIONS ..:://
void Level::Init()
{
	m_debugShader.Init("DebugShader", false);
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
	m_vertices = (Vertex*)malloc(sizeof(Vertex) * length);
	m_vertices2 = (Vertex*)malloc(sizeof(Vertex) * length2);
	
	uint64_t i = 0;

	float scaler = 1.0f;

	for (uint64_t x = 0; x < SIZE_X; x++)
	{
		for (uint64_t y = 0; y < SIZE_Y; y++)
		{
			// Quad 1.
			m_vertices[i].position = glm::vec3((x + 0.5f), (y + 0.5f), -2.0f * scaler);
			m_vertices[i].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices[i + 1].position = glm::vec3((x + 0.5f), (y - 0.5f), -2.0f * scaler);
			m_vertices[i + 1].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 1].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices[i + 2].position = glm::vec3((x - 0.5f), (y + 0.5f), -2.0f * scaler);
			m_vertices[i + 2].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 2].texCoordsAlpha = glm::vec3(0.0f, 1.0f, -2.0f);

			m_vertices[i + 3].position = glm::vec3((x - 0.5f), (y + 0.5f), -2.0f * scaler);
			m_vertices[i + 3].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 3].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices[i + 4].position = glm::vec3((x + 0.5f), (y - 0.5f), -2.0f * scaler);
			m_vertices[i + 4].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 4].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices[i + 5].position = glm::vec3((x - 0.5f), (y - 0.5f), -2.0f * scaler);
			m_vertices[i + 5].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			m_vertices[i + 5].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);
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
			m_vertices2[i].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices2[i + 1].position = glm::vec3(x + 0.5f, y + 0.5f, -2.0f);
			m_vertices2[i + 1].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 1].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices2[i + 2].position = glm::vec3(x - 0.5f, y + 0.5f, -2.0f);
			m_vertices2[i + 2].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 2].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices2[i + 3].position = glm::vec3(x - 0.5f, (y + 0.5f), 2.0f);
			m_vertices2[i + 3].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 3].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices2[i + 4].position = glm::vec3(x + 0.5f, y + 0.5f, 2.0f);
			m_vertices2[i + 4].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 4].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			m_vertices2[i + 5].position = glm::vec3(x - 0.5f, y + 0.5f, -2.0f);
			m_vertices2[i + 5].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			m_vertices2[i + 5].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

			// Quad 3.
			m_vertices2[i + 6].position = glm::vec3(x + 0.5f, y + 0.5f, 2.0f);
			m_vertices2[i + 6].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 6].texCoordsAlpha = glm::vec3(0.0f, 0.0f, 0.0f);

			m_vertices2[i + 7].position = glm::vec3(x + 0.5f, y - 0.5f, -2.0f);
			m_vertices2[i + 7].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 7].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices2[i + 8].position = glm::vec3(x + 0.5f, y + 0.5f, -2.0f);
			m_vertices2[i + 8].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 8].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices2[i + 9].position = glm::vec3(x + 0.5f, y + 0.5f, 2.0f);
			m_vertices2[i + 9].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 9].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices2[i + 10].position = glm::vec3(x + 0.5f, y - 0.5f, 2.0f);
			m_vertices2[i + 10].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 10].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			m_vertices2[i + 11].position = glm::vec3(x + 0.5f, y - 0.5f, -2.0f);
			m_vertices2[i + 11].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			m_vertices2[i + 11].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 0.0f);

			i += 12;
		}
	}


	m_mesh.LoadMesh(m_vertices, length);
	m_mesh2.LoadMesh(m_vertices2, length2);
}

void Level::UpdateIsOccupied(uint32_t posX, uint32_t posY, bool isOccupied)
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

	pos = (posY - SIZE_Y +(posX * SIZE_Y)) * 12;

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
