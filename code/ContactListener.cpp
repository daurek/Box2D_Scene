#include "ContactListener.hpp"
#include "RigidBody.hpp"
#include <iostream>

namespace rigid
{
	void ContactListener::BeginContact(b2Contact * contact)
	{
		void* firstUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void* secondUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		if (firstUserData && secondUserData)
		{
			RigidBody * firstRigidBody = static_cast<RigidBody*>(firstUserData);
			RigidBody * secondRigidBody = static_cast<RigidBody*>(secondUserData);
			firstRigidBody->StartContact(*secondRigidBody);
			secondRigidBody->StartContact(*firstRigidBody);
		}
	}

	void ContactListener::EndContact(b2Contact * contact)
	{

	}
}

