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
std::vector<Box> Collider2D::GetBoxes()
{
	return m_boxes;
}
void Collider2D::DrawCollider(Camera camera)
{
	Transform transf;
	transf.SetPosition(42.0, 24.0, -0.0);
	m_shader.Update(transf, camera);
	m_mesh.Render();

}

void Collider2D::CreateBoundingBoxes(b2World* world) {


	m_imp.ImportLevel(m_level);

	const uint64_t length = SIZE_X * SIZE_Y * 6;
	m_vertices = (Vertex2D*)malloc(sizeof(Vertex2D) * length);
	uint64_t i = 0;
	float scaler = 1.0f;
	GLuint blocksInRow = 0.0;
	GLfloat offset = 0.0f;
	GLfloat blockScale = 0.4;

	//IF pos(X,Y) IS OCCUPIED BY BLOCK, FILL WITH BOUNDING BOX
	for (uint64_t y = 1; y < SIZE_Y; y++)

	{
		for (uint64_t x = 1; x < SIZE_X; x++)
		{

			if (m_level.GetIsOccupied(x, y)) {
				for (int index = x + 1; m_level.GetIsOccupied(index, y); index++) {

					blocksInRow += 1;

				}
				
				offset = (blocksInRow);
				
				//From current X, check next cells until next cell is empty in order to decide lenght of bounding box.
				m_vertices[i].position = glm::vec2((x + blockScale) + offset, (y + blockScale));

				m_vertices[i + 1].position = glm::vec2((x + blockScale)+offset, (y - blockScale));
													 
				m_vertices[i + 2].position = glm::vec2((x - blockScale), (y + blockScale));
													 
				m_vertices[i + 3].position = glm::vec2((x - blockScale), (y + blockScale));
													 
				m_vertices[i + 4].position = glm::vec2((x + blockScale)+offset, (y - blockScale));
													 
				m_vertices[i + 5].position = glm::vec2((x - blockScale), (y - blockScale));


				Box test;

				GLint tempX, tempY;
				tempX = x;
				tempY = y;
				GLfloat scale = 0.5f;
				test.initStatic(world, glm::vec2((tempX), (tempY)), glm::vec2(offset, scale));

				test.getFixture()->SetFriction(5.0);
				test.getFixture()->SetRestitution(0.0);


				m_boxes.push_back(test);

				x += blocksInRow;
				blocksInRow = 0;
				i += 6;
			}
		}
	}

	m_mesh.LoadMesh(m_vertices, length);


}

void Collider2D::CreatePlayerBoundingBox(b2World* world) {

	Box tempBox;



	//SIZE OF THE PLAYER BOUNDING BOXZ
	tempBox.initDynamic(world, glm::vec2(42.0, 24.0), glm::vec2(0.5, 0.5));
	
	m_boxes.push_back(tempBox);



	//Player player;
	//glm::vec2=player.GetPosition();
	//test.initStatic(world, glm::vec2((tempX), (tempY)), glm::vec2(offset / 99, scale));

}