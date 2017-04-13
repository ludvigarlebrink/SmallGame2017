#include "Collider2D.h"



Collider2D::Collider2D()
{
	m_shader.Init("ColliderShader", false, false);
}


Collider2D::~Collider2D()
{
}

void Collider2D::SetBoxCollider(glm::vec2 min, glm::vec2 max)
{


}

void Collider2D::ImportLevel(Level level) {



	m_level = level;

}
void Collider2D::DrawCollider(Camera camera)
{
	m_shader.Bind();
	m_shader.Update(m_transform, camera);
	m_mesh.Render();

}

void Collider2D::CreateBoundingBoxes() {


	m_imp.ImportLevel(m_level);

	const uint64_t length = SIZE_X * SIZE_Y * 6;
	m_vertices = (Vertex3D*)malloc(sizeof(Vertex3D) * length);
	uint64_t i = 0;
	float scaler = 1.0f;
	GLuint blocksInRow = 0.0;
	GLfloat offset = 0.0f;

	//IF pos(X,Y) IS OCCUPIED BY BLOCK, FILL WITH BOUNDING BOX
	for (uint64_t y = 1; y < SIZE_Y; y++)

	{


		for (uint64_t x = 0; x < SIZE_X; x++)
		{

			if (m_level.GetIsOccupied(x, y)) {
				for (int index = x + 1; m_level.GetIsOccupied(index, y); index++) {

					blocksInRow += 1;

				}
				std::cout << blocksInRow << std::endl;
				
				offset = (blocksInRow);
				std::cout << offset << std::endl;

				//From current X, check next cells until next cell is empty in order to decide lenght of bounding box.
				m_vertices[i].position = glm::vec3((x + 0.4)+offset, (y + 0.4), -2.0f * scaler);
				m_vertices[i].normal = glm::vec3(0.0f, 0.0f, -1.0f);
				m_vertices[i].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

				m_vertices[i + 1].position = glm::vec3((x + 0.4)+offset, (y - 0.4), -2.0f * scaler);
				m_vertices[i + 1].normal = glm::vec3(0.0f, 0.0f, -1.0f);
				m_vertices[i + 1].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

				m_vertices[i + 2].position = glm::vec3((x - 0.4), (y + 0.4), -2.0f * scaler);
				m_vertices[i + 2].normal = glm::vec3(0.0f, 0.0f, -1.0f);
				m_vertices[i + 2].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

				m_vertices[i + 3].position = glm::vec3((x - 0.4), (y + 0.4), -2.0f * scaler);
				m_vertices[i + 3].normal = glm::vec3(0.0f, 0.0f, -1.0f);
				m_vertices[i + 3].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

				m_vertices[i + 4].position = glm::vec3((x + 0.4)+offset, (y - 0.4), -2.0f * scaler);
				m_vertices[i + 4].normal = glm::vec3(0.0f, 0.0f, -1.0f);
				m_vertices[i + 4].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

				m_vertices[i + 5].position = glm::vec3((x - 0.4), (y - 0.4f), -2.0f * scaler);
				m_vertices[i + 5].normal = glm::vec3(0.0f, 0.0f, -1.0f);
				m_vertices[i + 5].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);


				//m_vertices[i + 0].position.x += offset;
				//m_vertices[i + 1].position.x += offset;
				//m_vertices[i + 2].position.x += offset;
				//m_vertices[i + 3].position.x += offset;
				//m_vertices[i + 4].position.x += offset;
				//m_vertices[i + 5].position.x += offset;

	/*			m_vertices[i + 0].position.x *= offset;
				m_vertices[i + 1].position.x *= offset;
				m_vertices[i + 2].position.x *= offset;
				m_vertices[i + 3].position.x *= offset;
				m_vertices[i + 4].position.x *= offset;
				m_vertices[i + 5].position.x *= offset;*/


				x += blocksInRow;
				blocksInRow = 0;
				i += 6;
			}
		}
	}






	m_mesh.LoadMesh(m_vertices, length);


}