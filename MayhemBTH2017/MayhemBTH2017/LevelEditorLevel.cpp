#include "LevelEditorLevel.h"



LevelEditorLevel::LevelEditorLevel()
{
	Init();
}


LevelEditorLevel::~LevelEditorLevel()
{

}

void LevelEditorLevel::Render()
{
	// SELECT THE SHADER
	// UPDATE THE SHADER
	m_debugShader.Bind();

	for (uint32_t x = 0; x < SIZE_X; x++)
	{
		for (uint32_t y = 0; y < SIZE_Y; y++)
		{
			m_debugShader.Update(m_meshObjects[x][y].transform, m_camera);
			if (m_grid[x][y].isOccupied)
			{
				m_meshObjects[x][y].mesh.Render();
			}
		}
	}
}

void LevelEditorLevel::SetTexture(uint32_t posX, uint32_t posY, uint32_t textureID)
{
	m_grid[posX][posY].textureID = textureID;
}

void LevelEditorLevel::SetOccupied(uint32_t posX, uint32_t posY, bool isOccupied)
{
	m_grid[posX][posY].isOccupied = isOccupied;
}

void LevelEditorLevel::SetSpawnPoint(uint32_t posX, uint32_t posY, bool isSpawnPoint)
{
	m_grid[posX][posY].isSpawnPoint = isSpawnPoint;
}


//::.. GET FUNCTIONS ..:://
bool LevelEditorLevel::GetOccupied(uint32_t posX, uint32_t posY)
{
	return m_grid[posX][posY].isOccupied;
}

bool LevelEditorLevel::GetIsSpawnPoint(uint32_t posX, uint32_t posY)
{
	return m_grid[posX][posY].isSpawnPoint;
}

uint32_t LevelEditorLevel::GetTextureID(uint32_t posX, uint32_t posY)
{
	return m_grid[posX][posY].textureID;
}

void LevelEditorLevel::AddBlock(uint32_t posX, uint32_t posY)
{
	SetOccupied(posX, posY, !GetOccupied(posX, posY));
}

void LevelEditorLevel::AddSpawnPoint(uint32_t posX, uint32_t posY)
{
	if (!GetOccupied(posX, posY))
	{
		SetSpawnPoint(posX, posY, !GetIsSpawnPoint);
	}
}


//::.. HELP FUNCTIONS ..:://
void LevelEditorLevel::Init()
{
	m_debugShader.Init("DebugShader", false);
	InitGrid();
	InitMeshes();
}

void LevelEditorLevel::InitGrid()
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

void LevelEditorLevel::InitMeshes()
{
	for (size_t x = 0; x < SIZE_X; x++)
	{
		for (size_t y = 0; y < SIZE_Y; y++)
		{
			Vertex verts[6];

			verts[0].position = glm::vec3(0.5f, 0.5f, 0.0f);
			verts[0].normal = glm::vec3(0.5f, 0.5f, 0.0f);
			verts[0].texCoords = glm::vec2(0.0f, 1.0f);

			verts[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
			verts[1].normal = glm::vec3(1.0f, 1.0f, 0.0f);
			verts[1].texCoords = glm::vec2(0.0f, 1.0f);

			verts[2].position = glm::vec3(-0.5f, 0.5f, 0.0f);
			verts[2].normal = glm::vec3(1.0f, 1.0f, 0.0f);
			verts[2].texCoords = glm::vec2(0.0f, 1.0f);

			verts[3].position = glm::vec3(0.5f, -0.5f, 0.0f);
			verts[3].normal = glm::vec3(1.0f, 1.0f, 0.0f);
			verts[3].texCoords = glm::vec2(0.0f, 1.0f);

			verts[4].position = glm::vec3(-0.5f, 0.5f, 0.0f);
			verts[4].normal = glm::vec3(1.0f, 1.0f, 0.0f);
			verts[4].texCoords = glm::vec2(0.0f, 1.0f);

			verts[5].position = glm::vec3(-0.5f, -0.5f, 0.0f);
			verts[5].normal = glm::vec3(1.0f, 1.0f, 0.0f);
			verts[5].texCoords = glm::vec2(0.0f, 1.0f);

			Transform tmpTransform;
			tmpTransform.SetPosition(x * 2, y * 2, 100);
			m_meshObjects[x][y].transform = tmpTransform;
			m_meshObjects[x][y].mesh.LoadMesh(verts, 6, 3);
		}
	}
}