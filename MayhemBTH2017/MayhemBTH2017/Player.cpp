#include "Player.h"

Player::Player(b2World* world, glm::vec2 pos, glm::vec2 scale) {
	
	Init(world, pos, scale);
}

Player::Player()
{

}


Player::~Player()
{
}

void Player::Init(b2World* world, glm::vec2 pos, glm::vec2 scale)
{
	//Initiate the players bounding box
	m_boundingBox.initDynamic(world, pos, scale);
	
	//Load player MESH
	m_playerMesh = m_meshImp.Import();

	//Load player shader
	m_shader.Init(".\\Assets\\GLSL\\ToonShader", 0, 0);

	

}

void Player::Update() {

	
	

}

Box Player::GetBox()
{
	return m_boundingBox;
}


void Player::Render(Transform transform, Camera camera) {
	
	m_shader.Bind();
	m_shader.Update(transform, camera);


	m_playerMesh.Render();

}

