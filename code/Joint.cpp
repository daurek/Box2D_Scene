#include "Joint.hpp"
#include "RigidBody.hpp"


namespace rigid
{
	Joint::Joint(std::shared_ptr<b2World> physicsWorld, RigidBody first, RigidBody second, b2JointType _type)
	{
		jointDef.bodyA = first.body;
		jointDef.bodyB = second.body;
		jointDef.type = _type;
		jointDef.collideConnected = false;
		joint = physicsWorld->CreateJoint(&jointDef);
	}
}

