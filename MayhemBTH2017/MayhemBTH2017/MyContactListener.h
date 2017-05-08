#ifndef __MYCONTACTLISTENER_H__
#define	__MYCONTACTLISTENER_H__

#include "Player.h"
#include "Projectile.h"
#include "PowerUp.h"
#include "Collider2D.h"

#include <box2d.h>

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();
	virtual ~MyContactListener();

	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);
};

#endif // !__MYCONTACTLISTENER_H__
