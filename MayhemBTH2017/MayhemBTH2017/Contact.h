
#ifndef __CONTACT_H__
#define __CONTACT_H__

#include "box2d.h"
#include "Player.h"
#include "Projectile.h"
#include "Collider2D.h"

class Contact :
	public b2ContactListener
{
public:

	Contact();
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	~Contact();
};

#endif
