#include "MyContactListener.h"



MyContactListener::MyContactListener()
{
}


MyContactListener::~MyContactListener()
{
}

void MyContactListener::BeginContact(b2Contact * contact)
{

	b2Fixture * fa = contact->GetFixtureA();
	b2Fixture * fb = contact->GetFixtureB();

	if (fa == NULL || fb == NULL)
		return;

	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();

	if (bodyUserData)
		static_cast<Player*>(bodyUserData)->StartContact();



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

	//check if fixture A was a Player
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Player*>(bodyUserData)->EndContact();

	//check if fixture B was a Projectile
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Projectile*>(bodyUserData)->EndContact();

}
