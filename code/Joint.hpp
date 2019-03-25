#pragma once
#include <Box2D/Box2D.h>

namespace rigid
{
	class RigidBody;

	class Joint
	{

	public:

		Joint(b2World & physicsWorld, std::shared_ptr<RigidBody> first, std::shared_ptr<RigidBody> second, b2JointDef * jointDef);
		
		b2Joint * joint;
	};

}