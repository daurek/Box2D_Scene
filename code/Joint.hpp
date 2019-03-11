#pragma once
#include <Box2D/Box2D.h>

namespace rigid
{
	class RigidBody;

	class Joint
	{

	public:

		Joint(std::shared_ptr< b2World > physicsWorld, RigidBody first, RigidBody second, b2JointType _type);
		
		b2JointDef jointDef;
		b2Joint * joint;
	};

}