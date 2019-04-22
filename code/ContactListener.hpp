/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::ContactListener
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

#include <Box2D/Box2D.h>

namespace rigid
{
	/// Collision Listener that handles messaging both GameObjects when a collision occurs
	class ContactListener : public b2ContactListener
	{

	public:

		ContactListener() {};

		// Called when two fixtures begin to touch
		void BeginContact(b2Contact* contact) override;

		// Called when two fixtures cease to touch
		void EndContact(b2Contact* contact) override;

	};

}