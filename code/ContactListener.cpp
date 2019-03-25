#include "ContactListener.hpp"
#include "Elevator.hpp"
#include <iostream>

namespace rigid
{
	void ContactListener::BeginContact(b2Contact * contact)
	{
		//RigidBody * firstUserData = static_cast<RigidBody*>(contact->GetFixtureA()->GetBody()->GetUserData());
		//RigidBody * secondUserData = static_cast<RigidBody*>(contact->GetFixtureB()->GetBody()->GetUserData());

		//if (firstUserData != NULL && secondUserData != NULL)
		//{
		////	std::cout << firstUserData->shape->getPosition().x << std::endl;
		////	firstUserData->StartContact(secondUserData);
		////	RigidBody * firstRigidBody = static_cast<RigidBody*> (firstUserData);
		////	RigidBody * secondRigidBody = static_cast<RigidBody*>(secondUserData);
		////	firstRigidBody->StartContact(secondRigidBody);
		////	//static_cast<Elevator *>(firstRigidBody)->StartContact(*secondRigidBody);
		////	/*if (firstRigidBody != nullptr && secondRigidBody != nullptr)
		////	{
		////		static_cast<Elevator *>(firstRigidBody)->StartContact(*secondRigidBody);
		////	}*/
		////	
		////	//secondRigidBody->StartContact(*firstRigidBody);
		//}
	}

	void ContactListener::EndContact(b2Contact * contact)
	{

	}
}

