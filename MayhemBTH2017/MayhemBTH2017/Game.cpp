#include "Game.h"

#include <iomanip>

Game::Game()
{

	
	

	//Init toon shader for player
	m_toonShader.Init("ToonShader", 0, 0);
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
	if (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY) != 0.0f || m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX) != 0.0f)
	{


		tran.SetPosition(tran.GetPosition().x - 10.0f * m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX)*time->GetDeltaTime() , 24.0, 0.0);
		
	}

	//Right stick
	if (m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTY) != 0.0f || m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) != 0.0f)
	{

		tran.SetPosition(tran.GetPosition().x - 0.6*m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTX)*	time->GetDeltaTime(), 24.0, 0.0);
	}

	m_toonShader.Bind();

	m_toonShader.Update(tran, cam);
	m_player.Render();

}

void Game::Render() {

}

glm::vec3 Game::GetPlayerPos() {

	return tran.GetPosition();
}