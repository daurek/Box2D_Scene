#include "Joint.hpp"
#include "RigidBody.hpp"


namespace rigid
{
	Joint::Joint(b2World & physicsWorld, std::shared_ptr<RigidBody> first, std::shared_ptr<RigidBody> second, b2JointDef * jointDef)
	{
		jointDef->bodyA = first->body;
		jointDef->bodyB = second->body;
		jointDef->collideConnected = false;
		joint = physicsWorld.CreateJoint(jointDef);
	}
}

