/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Elevator
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Project
#include "GameObject.hpp"

namespace rigid
{
	/// Handles Movement between 2 points
	class Elevator : public GameObject
	{
	public:

		using GameObject::GameObject;

		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Reset() override;
		virtual void StartContact(GameObject * contactBody) override;
		virtual void EndContact(GameObject * contactBody) override;

	private:

		/// Caching elevator RigidBody
		std::shared_ptr< RigidBody >	elevator;
		/// Elevator joint reference
		b2PrismaticJoint			  *	elevatorJoint;
		/// Elevator timer to reset and go down
		float							timer;
		/// If the car is inside
		bool							inside = false;
	};

	
	

}