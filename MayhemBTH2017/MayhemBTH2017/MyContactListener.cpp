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

	/*skullStruct * skull = dynamic_cast<skullStruct*>(bodyUserData);
	Player * playa = dynamic_cast<Player*>(bodyUserData2);

	if ((skull != nullptr) && (playa != nullptr))
	{
		playa->StartContact(false, false, true, skull->skullID);
		skull->collided = true;
	}*/

	/*bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * playa2 = dynamic_cast<Player*>(bodyUserData);
	skullStruct * skull2 = dynamic_cast<skullStruct*>(bodyUserData2);

	if ((playa2 != nullptr) && (skull2 != nullptr))
	{
		playa2->StartContact(false, false, true, skull2->skullID);
		skull2->collided = true;
	}*/
	
	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Projectile * proj = dynamic_cast<Projectile*>(bodyUserData);
	Player * player = dynamic_cast<Player*>(bodyUserData2);

	if ((proj != nullptr) && (player != nullptr))
	{
		static_cast<Projectile*>(bodyUserData)->StartContact();
		static_cast<Player*>(bodyUserData2)->StartContact(true, false, false, -1);
		PostProcessingManager::SetState(PostProcessingManager::SHAKE);

		static_cast<Player*>(bodyUserData2)->Hit(static_cast<Projectile*>(bodyUserData)->GetProjectileID());

	}

	bodyUserData  = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player1 = dynamic_cast<Player*>(bodyUserData);
	Projectile * proj1 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((player1 != nullptr) && (proj1 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->StartContact(true, false, false, -1);
		static_cast<Projectile*>(bodyUserData2)->StartContact();

		PostProcessingManager::SetState(PostProcessingManager::SHAKE);

		static_cast<Player*>(bodyUserData)->Hit(static_cast<Projectile*>(bodyUserData2)->GetProjectileID());
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Projectile * proj3 = dynamic_cast<Projectile*>(bodyUserData);
	Collider2D * col2d = dynamic_cast<Collider2D*>(bodyUserData2);

	if ((proj3 != nullptr) && (col2d != nullptr))
	{
		static_cast<Projectile*>(bodyUserData)->StartContact();
		static_cast<Projectile*>(bodyUserData)->CollisionTrue();
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Projectile * proj2 = dynamic_cast<Projectile*>(bodyUserData2);
	Collider2D * col2d2 = dynamic_cast<Collider2D*>(bodyUserData);

	if ((proj2 != nullptr) && (col2d2 != nullptr))
	{
		static_cast<Projectile*>(bodyUserData2)->StartContact();
		static_cast<Projectile*>(bodyUserData2)->CollisionTrue();
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player3 = dynamic_cast<Player*>(bodyUserData);
	PowerUp * pu1 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player3 != nullptr) && (pu1 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->StartContact(false, true, false, -1);
		static_cast<PowerUp*>(bodyUserData2)->CollidedWithPlayer(true);
	}


	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	PowerUp * pu = dynamic_cast<PowerUp*>(bodyUserData);
	Player * player2 = dynamic_cast<Player*>(bodyUserData2);

	if ((pu != nullptr) && (player2 != nullptr))
	{
		static_cast<PowerUp*>(bodyUserData)->CollidedWithPlayer(true);
		static_cast<Player*>(bodyUserData2)->StartContact(false, true, false, -1);
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player4 = dynamic_cast<Player*>(bodyUserData);
	PowerUp * pu2 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player3 != nullptr) && (pu1 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->StartContact(false, true, false, -1);
		static_cast<PowerUp*>(bodyUserData2)->CollidedWithPlayer(true);
	}
}

void MyContactListener::EndContact(b2Contact * contact)
{

	Collidable * bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Collidable * bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	//skullStruct * skull = dynamic_cast<skullStruct*>(bodyUserData);
	//Player * player5 = dynamic_cast<Player*>(bodyUserData2);

	//if ((skull != nullptr) && (player5 != nullptr))
	//{
	//	static_cast<skullStruct*>(bodyUserData)->collided = false;
	//	static_cast<Player*>(bodyUserData2)->EndContact();
	//}

	/*bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());*/

	//Player * player9 = dynamic_cast<Player*>(bodyUserData);
	//skullStruct * skull2 = dynamic_cast<skullStruct*>(bodyUserData2);

	//if ((skull2 != nullptr) && (player9 != nullptr))
	//{
	//	static_cast<Player*>(bodyUserData)->EndContact();
	//	static_cast<skullStruct*>(bodyUserData2)->collided = false;
	//}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Projectile * proj = dynamic_cast<Projectile*>(bodyUserData);
	Player * player = dynamic_cast<Player*>(bodyUserData2);

	if ((proj != nullptr) && (player != nullptr))
	{
		static_cast<Projectile*>(bodyUserData)->EndContact();
		static_cast<Player*>(bodyUserData2)->EndContact();
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

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Projectile * proj3 = dynamic_cast<Projectile*>(bodyUserData);
	Collider2D * col2d = dynamic_cast<Collider2D*>(bodyUserData2);

	if ((proj3 != nullptr) && (col2d != nullptr))
	{
		static_cast<Projectile*>(bodyUserData)->EndContact();
		static_cast<Projectile*>(bodyUserData)->CollisionTrue();
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Projectile * proj2 = dynamic_cast<Projectile*>(bodyUserData2);
	Collider2D * col2d2 = dynamic_cast<Collider2D*>(bodyUserData);

	if ((proj2 != nullptr) && (col2d2 != nullptr))
	{
		static_cast<Projectile*>(bodyUserData2)->EndContact();
		static_cast<Projectile*>(bodyUserData2)->CollisionTrue();
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player3 = dynamic_cast<Player*>(bodyUserData);
	PowerUp * pu1 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player3 != nullptr) && (pu1 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->EndContact();
	}


	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	PowerUp * pu = dynamic_cast<PowerUp*>(bodyUserData);
	Player * player2 = dynamic_cast<Player*>(bodyUserData2);

	if ((pu != nullptr) && (player2 != nullptr))
	{
		static_cast<Player*>(bodyUserData2)->EndContact();
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player4 = dynamic_cast<Player*>(bodyUserData);
	PowerUp * pu2 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player3 != nullptr) && (pu1 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->EndContact();
	}
}
