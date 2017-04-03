#include "LevelEditor.h"

//Used for debugging
#include <iostream>

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
	for (uint32_t x = 0; x < SIZE_X; x++)
	{
		for (uint32_t y = 0; y < SIZE_Y; y++)
		{
			if (!m_grid[x][y].isOccupied)
			{
				m_meshes[x][y].Render();
			}
		}
	}
}

void LevelEditor::SetTexture(uint32_t posX, uint32_t posY)
{

}

void LevelEditor::SetOccupied(uint32_t posX, uint32_t posY)
{

}

void LevelEditor::SetSpawnPoint(uint32_t posX, uint32_t posY)
{

}

void LevelEditor::SaveLevel()
{

}


//::.. HELP FUNCTIONS ..:://
void LevelEditor::Init()
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

}