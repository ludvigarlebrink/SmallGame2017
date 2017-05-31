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
	
	// Projectile

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player1Projectile = dynamic_cast<Player*>(bodyUserData2);
	Projectile * projectile1 = dynamic_cast<Projectile*>(bodyUserData);

	if ((player1Projectile != nullptr) && (projectile1 != nullptr))
	{
		static_cast<Projectile*>(bodyUserData)->StartContact();
		static_cast<Player*>(bodyUserData2)->StartContact(true, false, false);
		PostProcessingManager::SetState(PostProcessingManager::SHAKE);

		static_cast<Player*>(bodyUserData2)->Hit(static_cast<Projectile*>(bodyUserData)->GetProjectileID());

	}

	bodyUserData  = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player2Projectile = dynamic_cast<Player*>(bodyUserData);
	Projectile * projectile2 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((player2Projectile != nullptr) && (projectile2 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->StartContact(true, false, false);
		static_cast<Projectile*>(bodyUserData2)->StartContact();

		PostProcessingManager::SetState(PostProcessingManager::SHAKE);

		static_cast<Player*>(bodyUserData)->Hit(static_cast<Projectile*>(bodyUserData2)->GetProjectileID());
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player3Projectile = dynamic_cast<Player*>(bodyUserData);
	Projectile * projectile3 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((player3Projectile != nullptr) && (projectile3 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->StartContact(true, false, false);
		static_cast<Projectile*>(bodyUserData2)->StartContact();

		PostProcessingManager::SetState(PostProcessingManager::SHAKE);

		static_cast<Player*>(bodyUserData)->Hit(static_cast<Projectile*>(bodyUserData2)->GetProjectileID());
	}

	Player * player4Projectile = dynamic_cast<Player*>(bodyUserData);
	Projectile * projectile4 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((player4Projectile != nullptr) && (projectile4 != nullptr))
	{
		static_cast<Player*>(bodyUserData)->StartContact(true, false, false);
		static_cast<Projectile*>(bodyUserData2)->StartContact();

		PostProcessingManager::SetState(PostProcessingManager::SHAKE);

		static_cast<Player*>(bodyUserData)->Hit(static_cast<Projectile*>(bodyUserData2)->GetProjectileID());
	}

	// Collider

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Collider2D * col2d1 = dynamic_cast<Collider2D*>(bodyUserData2);
	Projectile * proj1 = dynamic_cast<Projectile*>(bodyUserData);

	if ((col2d1 != nullptr) && (proj1 != nullptr))
	{
		static_cast<Projectile*>(bodyUserData)->StartContact();
		static_cast<Projectile*>(bodyUserData)->CollisionTrue();
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Collider2D * col2d2 = dynamic_cast<Collider2D*>(bodyUserData);
	Projectile * proj2 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((col2d2 != nullptr) && (proj2 != nullptr))
	{
		static_cast<Projectile*>(bodyUserData2)->StartContact();
		static_cast<Projectile*>(bodyUserData2)->CollisionTrue();
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Collider2D * col2d3 = dynamic_cast<Collider2D*>(bodyUserData);
	Projectile * proj3 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((col2d3 != nullptr) && (proj3 != nullptr))
	{
		static_cast<Projectile*>(bodyUserData2)->StartContact();
		static_cast<Projectile*>(bodyUserData2)->CollisionTrue();
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Collider2D * col2d4 = dynamic_cast<Collider2D*>(bodyUserData);
	Projectile * proj4 = dynamic_cast<Projectile*>(bodyUserData2);

	if ((col2d4 != nullptr) && (proj4 != nullptr))
	{
		static_cast<Projectile*>(bodyUserData2)->StartContact();
		static_cast<Projectile*>(bodyUserData2)->CollisionTrue();
	}

	// Power Up

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player1 = dynamic_cast<Player*>(bodyUserData);
	PowerUp * powerUp1 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player1 != nullptr) && (powerUp1 != nullptr) && (powerUp1->GetFilter().categoryBits == POWERUP))
	{
		static_cast<Player*>(bodyUserData)->StartContact(false, true, false);
		static_cast<PowerUp*>(bodyUserData2)->CollidedWithPlayer(true);
	}


	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player2 = dynamic_cast<Player*>(bodyUserData2);
	PowerUp * powerUp2 = dynamic_cast<PowerUp*>(bodyUserData);

	if ((player2 != nullptr) && (powerUp2 != nullptr) && (powerUp2->GetFilter().categoryBits == POWERUP))
	{
		static_cast<PowerUp*>(bodyUserData)->CollidedWithPlayer(true);
		static_cast<Player*>(bodyUserData2)->StartContact(false, true, false);
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player3 = dynamic_cast<Player*>(bodyUserData);
	PowerUp * powerUp3 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player3 != nullptr) && (powerUp3 != nullptr) && (powerUp3->GetFilter().categoryBits == POWERUP))
	{
		static_cast<Player*>(bodyUserData)->StartContact(false, true, false);
		static_cast<PowerUp*>(bodyUserData2)->CollidedWithPlayer(true);
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player4 = dynamic_cast<Player*>(bodyUserData);
	PowerUp * powerUp4 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player4 != nullptr) && (powerUp4 != nullptr) && (powerUp4->GetFilter().categoryBits == POWERUP))
	{
		static_cast<Player*>(bodyUserData)->StartContact(false, true, false);
		static_cast<PowerUp*>(bodyUserData2)->CollidedWithPlayer(true);
	}

	// SKULL

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player1Skull = dynamic_cast<Player*>(bodyUserData);
	PowerUp * skull1 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player1Skull != nullptr) && (skull1 != nullptr) && (skull1->GetFilter().categoryBits == SKULL))
	{
		static_cast<Player*>(bodyUserData)->StartContact(false, false, true);
		static_cast<PowerUp*>(bodyUserData2)->CollidedWithPlayer(true);
		static_cast<Player*>(bodyUserData)->SetPointToGet(static_cast<PowerUp*>(bodyUserData2)->GetScore());
	}


	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player2Skull = dynamic_cast<Player*>(bodyUserData2);
	PowerUp * skull2 = dynamic_cast<PowerUp*>(bodyUserData);

	if ((player2Skull != nullptr) && (skull2 != nullptr) && (skull2->GetFilter().categoryBits == SKULL))
	{
		static_cast<PowerUp*>(bodyUserData)->CollidedWithPlayer(true);
		static_cast<Player*>(bodyUserData2)->StartContact(false, false, true);
		static_cast<Player*>(bodyUserData)->SetPointToGet(static_cast<PowerUp*>(bodyUserData2)->GetScore());
	}


	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player3Skull = dynamic_cast<Player*>(bodyUserData);
	PowerUp * skull3 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player3Skull != nullptr) && (skull3 != nullptr) && (skull3->GetFilter().categoryBits == SKULL))
	{
		static_cast<PowerUp*>(bodyUserData2)->CollidedWithPlayer(true);
		static_cast<Player*>(bodyUserData)->StartContact(false, false, true);
		static_cast<Player*>(bodyUserData)->SetPointToGet(static_cast<PowerUp*>(bodyUserData2)->GetScore());
	}

	bodyUserData = static_cast<Collidable*>(contact->GetFixtureA()->GetBody()->GetUserData());
	bodyUserData2 = static_cast<Collidable*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player * player4Skull = dynamic_cast<Player*>(bodyUserData);
	PowerUp * skull4 = dynamic_cast<PowerUp*>(bodyUserData2);

	if ((player4Skull != nullptr) && (skull4 != nullptr) && (skull4->GetFilter().categoryBits == SKULL))
	{
		static_cast<PowerUp*>(bodyUserData2)->CollidedWithPlayer(true);
		static_cast<Player*>(bodyUserData)->StartContact(false, false, true);
		static_cast<Player*>(bodyUserData)->SetPointToGet(static_cast<PowerUp*>(bodyUserData2)->GetScore());
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
