#include "Collider2D.h"



Collider2D::Collider2D()
{

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
	glUseProgram(0);
	m_level.Render(camera);
}

void Collider2D::CreateBoundingBoxes(b2World* world) {

	m_contact = false;
	m_imp.Import(m_level);

	
	const uint32_t length = SIZE_X * SIZE_Y * 6;
	m_vertices = (Vertex2D*)malloc(sizeof(Vertex2D) * length);
	
	uint32_t i = 0;
	float scaler = 1.0f;
	GLuint blocksInRow = 0.0;
	GLfloat offset = 0.0f;
	GLfloat blockScale = 0.4;

	//IF pos(X,Y) IS OCCUPIED BY BLOCK, FILL WITH BOUNDING BOX
	for (uint32_t y = 1; y < SIZE_Y; y++)

	{
		for (uint32_t x = 1; x < SIZE_X; x++)
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


				Box gameFloor;

				GLint tempX, tempY;
				tempX = x;
				tempY = y;
				GLfloat scale = 0.5f;

				gameFloor.InitStatic(world, glm::vec2((tempX-0.5), (tempY-0.5)), glm::vec2(offset+0.84, scale+0.42));
				gameFloor.getFixture()->SetRestitution(0.0); //floor bounciness
				gameFloor.getFixture()->SetFriction(1.0); //floor friction
				gameFloor.getBody()->ResetMassData();
			
				gameFloor.getBody()->SetUserData(this);
				b2Filter filter;
				filter.categoryBits = BOUNDARY;
				filter.maskBits = PLAYER|PROJECTILE;
				gameFloor.getFixture()->SetFilterData(filter);
			

				m_boxes.push_back(gameFloor);



				x += blocksInRow;
				blocksInRow = 0;
				i += 6;

			}
		}
	}

	m_mesh.Load(m_vertices, length);

	
}

void Collider2D::CreatePlayerBoundingBox(b2World* world) {

	Box tempBox;



	//SIZE OF THE PLAYER BOUNDING BOXZ
	tempBox.InitDynamic(world, glm::vec2(42.0, 24.0), glm::vec2(0.5, 0.5));
	
	m_boxes.push_back(tempBox);


}

uint16 Collider2D::GetMaskBits() {
	return m_boxes.at(0).GetMaskBits();
}

uint16 Collider2D::GetCategoryBits() {
	return m_boxes.at(0).GetCategoryBits();
	std::cout << m_boxes.at(0).GetCategoryBits() << std::endl;
}

void Collider2D::SetMaskBits(uint16 MASK) {
	
}

void Collider2D::SetCategoryBits(uint16 CATEGORY) {
	
}

void Collider2D::StartContact() { 
	m_contact = true; 
}
void Collider2D::EndContact() { 
	m_contact = false;
}