#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
	: m_posX(0), m_posY(0)
{
	Init();
}

LevelEditor::~LevelEditor()
{

}

void LevelEditor::Update()
{
	// SELECT THE SHADER
	// UPDATE THE SHADER

	for (uint32_t x = 0; x < SIZE_X; x++)
	{
		for (uint32_t y = 0; y < SIZE_Y; y++)
		{
			if (!m_grid[x][y].isOccupied)
			{
				m_meshObjects[x][y].mesh.Render();
			}
		}
	}
}

void LevelEditor::SetTexture(uint32_t textureID)
{
	m_grid[m_posX][m_posY].textureID = textureID;
}

void LevelEditor::SetOccupied(bool isOccupied)
{
	m_grid[m_posX][m_posY].textureID = isOccupied;
}

void LevelEditor::SetSpawnPoint(bool isSpawnPoint)
{
	m_grid[m_posX][m_posY].textureID = isSpawnPoint;
}

void LevelEditor::SaveLevel()
{
	// TODO: CALL THE LEVEL EXPORTER
}


//::.. HELP FUNCTIONS ..:://
void LevelEditor::Init()
{
	InitGrid();
	InitMeshes();
}

void LevelEditor::InitGrid()
{
	for (size_t x = 0; x < SIZE_X; x++)
	{
		for (size_t y = 0; y < SIZE_Y; y++)
		{
			m_grid[x][y].textureID = 0;
			m_grid[x][y].isOccupied = true;
			m_grid[x][y].isSpawnPoint = false;
		}
	}
}

void LevelEditor::InitMeshes()
{
	Vertex verts[6] =
	{
		// Triangle 1
		(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)),

		// Triangle 2
		(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f))
	};

	for (size_t x = 0; x < SIZE_X; x++)
	{
		for (size_t y = 0; y < SIZE_Y; y++)
		{
			Transform tmpTransform;
			tmpTransform.SetPosition(x, y, -10);
			m_meshObjects[x][y].transform = tmpTransform;
			m_meshObjects[x][y].mesh.LoadMesh(verts, 6, 3);
		}
	}
}
