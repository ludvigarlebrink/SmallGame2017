#ifndef __MYCONTACTLISTENER_H__
#define	__MYCONTACTLISTENER_H__

#include "Player.h"
#include "Projectile.h"

#include <box2d.h>

//class MyContactListener : public b2ContactListener
//{
//public:
//	MyContactListener();
//	virtual ~MyContactListener();
//
//	void BeginContact(b2Contact* contact) {
//
//		//check if fixture A was a ball
//		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//		if (bodyUserData)
//			static_cast<Player*>(bodyUserData)->StartContact();
//
//		//check if fixture B was a ball
//		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//		if (bodyUserData)
//			static_cast<Player*>(bodyUserData)->StartContact();
//
//	}
//
//	void EndContact(b2Contact* contact) {
//
//		//check if fixture A was a ball
//		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//		if (bodyUserData)
//			static_cast<Player*>(bodyUserData)->EndContact();
//
//		//check if fixture B was a ball
//		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//		if (bodyUserData)
//			static_cast<Player*>(bodyUserData)->EndContact();
//
//	}
//};

#endif // !__MYCONTACTLISTENER_H__
