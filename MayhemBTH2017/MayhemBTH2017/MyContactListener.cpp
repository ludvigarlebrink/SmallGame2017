#include "MyContactListener.h"



MyContactListener::MyContactListener()
{
}


MyContactListener::~MyContactListener()
{
}

void MyContactListener::BeginContact(b2Contact * contact)
{
	
	Collidable * bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Collidable * bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Projectile * proj1 = dynamic_cast<Projectile*>(bodyUserData);
	Projectile * proj2 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((proj1 != nullptr) && (proj2 != nullptr))
	{
		static_cast<Projectile*>(bodyUserData)->StartContact();
	}

	//check if fixture B was a ball


	std::cout << "Collision" << std::endl;

	////check if fixture A was a Player
	//void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	//if (bodyUserData)
	//	static_cast<Player*>(bodyUserData)->StartContact();

	////check if fixture B was a Projectile
	//bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	//if (bodyUserData)
	//	static_cast<Projectile*>(bodyUserData)->StartContact();

}

void MyContactListener::EndContact(b2Contact * contact)
{

	Projectile * bodyUserData = static_cast<Projectile*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Projectile * bodyUserData2 = static_cast<Projectile*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if ((bodyUserData->GetPrefab() != NULL) && (bodyUserData2->GetPrefab() != NULL))
	{
		static_cast<Projectile*>(bodyUserData)->EndContact();
	}

	std::cout << "No Collision..." << std::endl;

	//check if fixture A was a Player
}
