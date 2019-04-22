/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::ContactListener
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "ContactListener.hpp"

// Project
#include "GameObject.hpp"

namespace rigid
{
	void ContactListener::BeginContact(b2Contact * contact)
	{
		// Get both user data
		void * firstUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void * secondUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		// Check if they are valid and not the same
		if (firstUserData != nullptr && secondUserData != nullptr && firstUserData != secondUserData)
		{
			// Get both GameObjects
			GameObject * firstGameObject = static_cast<GameObject*>(firstUserData);
			GameObject * secondGameObject = static_cast<GameObject*>(secondUserData);

			// Check if their are valid
			if (firstGameObject != nullptr && secondGameObject != nullptr)
			{
				// Notify each other
				firstGameObject->StartContact(secondGameObject);
				secondGameObject->StartContact(firstGameObject);
			}
		}
	}

	void ContactListener::EndContact(b2Contact * contact)
	{
		// Get both user data
		void * firstUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void * secondUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		// Check if they are valid and not the same
		if (firstUserData != nullptr && secondUserData != nullptr && firstUserData != secondUserData)
		{
			GameObject * firstGameObject = static_cast<GameObject*>(firstUserData);
			GameObject * secondGameObject = static_cast<GameObject*>(secondUserData);

			// Check if their are valid
			if (firstGameObject != nullptr && secondGameObject != nullptr)
			{
				// Notify each other
				firstGameObject->EndContact(secondGameObject);
				secondGameObject->EndContact(firstGameObject);
			}
		}
	}
}

