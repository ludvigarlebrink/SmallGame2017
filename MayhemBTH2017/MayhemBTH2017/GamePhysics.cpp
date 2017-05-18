#include "GamePhysics.h"





GamePhysics::GamePhysics()
{
	m_loadWorld = false;
}

GamePhysics::~GamePhysics()
{

}

void GamePhysics::EnterWorld()
{

	//Get deltatime
	m_time = TimeManager::Get();
	b2Vec2 gravity(0.0f, -8.21f);

	m_world = std::make_unique<b2World>(gravity);

	m_floorCollider.CreateBoundingBoxes(m_world.get());

	//at global scope

	//in FooTest constructor

	m_world.get()->SetContactListener(new MyContactListener());

	//Set spawn position of player AND SIZE OF SPRITE BOX

	m_PH.Init(m_world.get(), 20);
	//PLAYER


	m_player[0].Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0, 5.0), 0);
	//m_player[0].SetMaskBits(POWERUP);

	m_player[1].Init(m_world.get(), glm::vec2(15, 24), glm::vec2(2.0, 5.0), 1);
	//m_player[1].SetMaskBits(POWERUP);
	m_nrOfPlayers = 2;

	///////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////

	//FIXTURES FOR COLLISIONS


	//player fixture is of type PLAYER
	m_loadWorld = true;
}

void GamePhysics::Update()
{

	switch (m_loadWorld) {
	case true:
	{
		m_world->Step(1.0f / 20.0f, 8, 5);
		int k = -1;
		for (int i = 0; i < m_nrOfPlayers; i++) {

			m_player[i].Update();
		}
		if (CreateRocketLauncherExplosion())
		{
			for (int i = 0; i < m_nrOfPlayers; i++)
			{
				if (m_player[i].GetWeapon().GetProjectiles().size() > 0)
				{
					k = i;
				}
			}
			for (int i = 0; i < m_nrOfPlayers; i++)
			{
				if (k > -1)
				{

					b2Vec2 fullVec = (m_player[i].GetBox().getBody()->GetPosition() - m_player[k].GetWeapon().GetFiredCurrentProjectilePos());

					b2Vec2 fullVec2 = (m_player[i].GetBox().getBody()->GetPosition() - m_player[k].GetWeapon().GetFiredCurrentProjectilePos());

					fullVec.Normalize();

					b2Vec2 radVec = b2Vec2(fullVec.x * 10.0f, fullVec.y * 10.0f);

					float force = 200;

					b2Vec2 finalVec = b2Vec2((radVec.x)*200/fullVec.Length(), (radVec.y)*200/fullVec.Length());

					m_player[i].GetBox().getBody()->ApplyForce(finalVec, m_player[i].GetBox().getBody()->GetWorldCenter(), true);

					m_player[k].GetWeapon().SetExplosion(false);

				}
			}
		}

		m_PH.Update();

		m_world->Step(1.0f / 20.0f, 8, 5); 
	}
	break;
	case false:
		std::cout << "LOADING" << std::endl;
		EnterWorld();
		break;
		//Update player bounding box sprite position to the position of the player mesh
	}
}

glm::vec3 GamePhysics::GetPosition() {

	return m_transform.GetPosition();

}

void GamePhysics::SetNrOfPlayers(int nrOf)
{
	m_nrOfPlayers = nrOf;
}

bool GamePhysics::CreateRocketLauncherExplosion()
{
	for (int j = 0; j < m_nrOfPlayers; j++)
	{
		if (m_player[j].GetWeapon().GetProjectiles().size() > 0)
		{
			if (m_player[j].GetWeapon().IsRocketLauncher() && m_player[j].GetWeapon().GetExplosion())
			{

				return true;
			}
		}
	}
	return false;
}

void GamePhysics::Render(Camera camera) {


	m_floorCollider.DrawCollider(camera);

	for (int i = 0; i < 2; i++) {

		m_player[i].Render(camera);
	}

	m_PH.Render(camera);

	glClear(GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 2; i++) {

		m_player[i].GetHealthBar()->Render(camera);
	}
}

