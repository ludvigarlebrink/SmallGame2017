#include "Text.h"



Text::Text()
{
	// Do nothing...
}


Text::~Text()
{
	// Do nothing...
}



void Text::Init()
{
	verts[0].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[0].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	verts[0].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	verts[1].position = glm::vec3(0.5f, 0.5f, 0.0f);
	verts[1].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	verts[1].texCoordsAlpha = glm::vec3(0.0f, 0.0f, 1.0f);

	verts[2].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[2].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	verts[2].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 1.0f);

	verts[3].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[3].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	verts[3].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 1.0f);

	verts[4].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[4].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	verts[4].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	verts[5].position = glm::vec3(-0.5f, -0.5f, 0.0f);
	verts[5].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	verts[5].texCoordsAlpha = glm::vec3(1.0f, 1.0f, 1.0f);

	m_mesh.Load(verts, 6);
}

void Text::Render()
{
	m_mesh.Render();
}