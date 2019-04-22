/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Joint
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Joint.hpp"

// Project
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

