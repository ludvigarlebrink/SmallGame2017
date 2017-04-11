#include "Game.h"



Game::Game()
{
	LevelImporter imp;
	imp.ImportLevel(m_level);

	int i = 0;

		m_vertices[i].position = glm::vec3(0.5f, 0.5f, 2.0f);
		m_vertices[i].normal = glm::vec3(0.0f, 1.0f, 0.0f);
		m_vertices[i].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

		m_vertices[i + 1].position = glm::vec3(0.5f, 0.5f, -2.0f);
		m_vertices[i + 1].normal = glm::vec3(0.0f, 1.0f, 0.0f);
		m_vertices[i + 1].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

		m_vertices[i + 2].position = glm::vec3(0.5f,0.5f, -2.0f);
		m_vertices[i + 2].normal = glm::vec3(0.0f, 1.0f, 0.0f);
		m_vertices[i + 2].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

		m_vertices[i + 3].position = glm::vec3(0.5f, (0.5f), 2.0f);
		m_vertices[i + 3].normal = glm::vec3(0.0f, 1.0f, 0.0f);
		m_vertices[i + 3].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

		m_vertices[i + 4].position = glm::vec3(0.5f,0.5f, 2.0f);
		m_vertices[i + 4].normal = glm::vec3(0.0f, 1.0f, 0.0f);
		m_vertices[i + 4].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

		m_vertices[i + 5].position = glm::vec3(0.5f, 0.5f, -2.0f);
		m_vertices[i + 5].normal = glm::vec3(0.0f, 1.0f, 0.0f);
		m_vertices[i + 5].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 0.0f);

}


Game::~Game()
{
}

void Game::Update(Camera cam){

	m_player.Render();
	m_level.Render(cam);
	m_player.LoadMesh(m_vertices, 6);

}

void Game::Render() {

	m_player.Render();
}