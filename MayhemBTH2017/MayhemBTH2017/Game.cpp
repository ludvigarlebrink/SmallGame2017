#include "Game.h"

#include <iomanip>

Game::Game()
{

	
	

	//Init toon shader for player
	m_toonShader.Init(".\\Assets\\GLSL\\ToonShader", 0, 0);
	LevelImporter imp;
	m_input = InputManager::Get();

	imp.ImportLevel(m_level);
	
	m_player = meshImp.Import();

	tran.SetPosition(42.0, 24.0, -0.0); //middle scren
	time = TimeManager::Get();

}


Game::~Game()
{
}

void Game::Update(Camera cam){

	m_level.Render(cam);
	//Left stick

	tran.SetPositionZ(-1.5);
	if (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY) != 0.0f || m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX) != 0.0f)
	{

		tran.SetPositionX(tran.GetPosition().x - 15.0f * m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*time->GetDeltaTime());

		
	}

	//Right stick
	if (m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTY) != 0.0f || m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) != 0.0f)
	{


		tran.SetPositionX(tran.GetPosition().x - 15.0f * m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*time->GetDeltaTime());
	}

	if (tran.GetPosition().y > 2.5f) {
		pos += pow(0.2f, 2.0f);
		tran.SetPositionY(18 - pos);
	}
	


}

void Game::Render() {

}

glm::vec3 Game::GetPlayerPos() {

	return tran.GetPosition();
}