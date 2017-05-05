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
	b2Vec2 gravity(0.0f, -5.21f);

	m_world = std::make_unique<b2World>(gravity);

	m_floorCollider.CreateBoundingBoxes(m_world.get());

	//at global scope

	//in FooTest constructor
	m_world.get()->SetContactListener(new MyContactListener());

	//Set spawn position of player AND SIZE OF SPRITE BOX

	//PLAYER
	m_player.Init(m_world.get(), glm::vec2(42, 24), glm::vec2(2.0, 2.0));

	///////////////////////////////////////////////////////////////////


	//m_weapon.InitParticleSystem(".\\Assets\\GLSL\\GeometryPass", glm::vec4(1.0, 0.0, 0.0, 1.0), 2.0f, 500);

	m_PH.Init(m_player, m_world.get(), 100);

	///////////////////////////////////////////////////////////////////

	//FIXTURES FOR COLLISIONS


	//player fixture is of type PLAYER
	m_player.SetCategoryBits(PLAYER);
	m_player.SetMaskBits(POWERUP);
	m_loadWorld = true;
}

void GamePhysics::Update()
{
	switch (m_loadWorld) {
	case true:
	{
		if (!(m_player.GetCategoryBits() & powerUpFixture.filter.maskBits) != 0 && (powerUpFixture.filter.categoryBits & m_player.GetMaskBits()) != 0) {

		}

		m_world->Step(1.0f / 30.0f, 6, 2);

		for (b2Contact* contact = m_world->GetContactList(); contact; contact = contact->GetNext())
		{
			if (contact->IsTouching())
			{
				Projectile* proj = static_cast<Projectile*>(contact->GetFixtureB()->GetBody()->GetUserData());
				if (proj != NULL)
				{
					//std::cout << " den nuddar något som kanske nuddar något osv .." << std::endl;
				}
			}

		}

		m_player.Update();

		m_PH.Update();

		m_world->Step(1.0f / 30.0f, 6, 2); }
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

void GamePhysics::Render(Camera camera) {
	camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
	m_floorCollider.DrawCollider(camera);

	m_player.Render(camera);

	m_PH.Render(camera);

	//m_weapon.RenderParticles(camera);

}