#pragma once
#include <Box2D/Box2D.h>

namespace rigid
{
	class ContactListener : public b2ContactListener
	{

	public:

		ContactListener() {};

		// Called when two fixtures begin to touch
		void BeginContact(b2Contact* contact);

		// Called when two fixtures cease to touch
		void EndContact(b2Contact* contact);

	};

}