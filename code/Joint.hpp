/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Joint
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
	class RigidBody;

	/// Box2D container class
	class Joint
	{
	public:

		/// Creates a Joint on given world and bodies with given definition
		Joint(b2World & physicsWorld, std::shared_ptr<RigidBody> first, std::shared_ptr<RigidBody> second, b2JointDef * jointDef);
		
		/// Joint reference
		b2Joint * joint;
	};

}