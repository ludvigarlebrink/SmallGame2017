#include "Contact.h"



Contact::Contact()
{
}



Contact::~Contact()
{
}

void Contact::BeginContact(b2Contact * contact)
{
	/*is body A type Projectile?*/
	void* bodyData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyData)
		static_cast<Projectile*>(bodyData)->StartContact();
	
	//is body B type Projectile?
	bodyData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyData)
		static_cast<Projectile*>(bodyData)->StartContact();

}

void Contact::EndContact(b2Contact * contact)
{
	/*is body A type Projectile?*/
	void* bodyData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyData)
		static_cast<Projectile*>(bodyData)->EndContact();

	//is body B type Projectile?
	bodyData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyData)
		static_cast<Projectile*>(bodyData)->EndContact();
}

