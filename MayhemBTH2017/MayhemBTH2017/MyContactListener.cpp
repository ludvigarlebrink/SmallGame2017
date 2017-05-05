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

	Projectile * proj = dynamic_cast<Projectile*>(bodyUserData);
	Player * player = dynamic_cast<Player*>(bodyUserData2);

	if ((proj != nullptr) && (player != nullptr))
	{
		static_cast<Projectile*>(bodyUserData)->StartContact();
		static_cast<Player*>(bodyUserData2)->StartContact(true, false);

		return;
	}

	bodyUserData  = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player1 = dynamic_cast<Player*>(bodyUserData);
	Projectile * proj1 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((player1 != nullptr) && (proj1 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->StartContact(true, false);
		static_cast<Projectile*>(bodyUserData2)->StartContact();

		return;

	}


	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	PowerUp * pu = dynamic_cast<PowerUp*>(bodyUserData);
	Player * player2 = dynamic_cast<Player*>(bodyUserData2);

	if ((pu != nullptr) && (player2 != nullptr))
	{
		static_cast<PowerUp*>(bodyUserData)->CollidedWithPlayer(true);
		static_cast<Player*>(bodyUserData2)->StartContact(false, true);

		return;
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player3 = dynamic_cast<Player*>(bodyUserData);
	PowerUp * pu1 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player3 != nullptr) && (pu1 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->StartContact(false, true);
		static_cast<PowerUp*>(bodyUserData2)->CollidedWithPlayer(true);
	}


	//std::cout << "Collision" << std::endl;

}

void MyContactListener::EndContact(b2Contact * contact)
{

	Collidable * bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Collidable * bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Projectile * proj = dynamic_cast<Projectile*>(bodyUserData);
	Player * player = dynamic_cast<Player*>(bodyUserData2);

	if ((proj != nullptr) && (player != nullptr))
	{
		static_cast<Projectile*>(bodyUserData)->EndContact();
		static_cast<Player*>(bodyUserData2)->EndContact();

		return;
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player1 = dynamic_cast<Player*>(bodyUserData);
	Projectile * proj1 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((player1 != nullptr) && (proj1 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->EndContact();
		static_cast<Projectile*>(bodyUserData2)->EndContact();
	}

	//std::cout << "No Collision..." << std::endl;

	//check if fixture A was a Player
}
