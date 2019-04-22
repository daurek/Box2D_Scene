/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::GameObject
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Project
#include "RigidBody.hpp"
#include "Joint.hpp"

namespace rigid
{
	/// Base GameObject Container with RigidBody and Joint maps along with some properties
	class GameObject
	{

	public:

		/// Default Constructor
		GameObject() {};

		/// GameObject Initial Setup
		virtual void Start() = 0;

		/// Renders each RigidBody with the given window
		virtual void Render(sf::RenderWindow & window);

		/// Custom Logic Update
		virtual void Update(float deltaTime) = 0;

		/// Custom Reset (User chooses to reset some rigidbodies or not)
		virtual void Reset() = 0;

		/// Custom Collision Detection on Start with the other given GameObject
		virtual void StartContact(GameObject * contactBody) = 0;

		/// Custom Collision Detection on End with the other given GameObject
		virtual void EndContact(GameObject * contactBody)   = 0;

		/// Adds given RigidBody to the list with the given name and sets it's user data to the current class instance
		void AddRigidbody(std::string name, std::shared_ptr< RigidBody > rigidBody)
		{
			rigidBody->body->SetUserData(this);
			rigidBodies[name] = rigidBody;
		}

		/// Adds given RigidBody to the list with the given name
		void AddJoint(std::string name, std::shared_ptr< Joint > joint)
		{
			joints[name] = joint;
		}

		/// Returns correct RigidBody with the given key
		std::shared_ptr< RigidBody > GetRigidBody(std::string name)
		{
			if (!rigidBodies.count(name))
				return nullptr;
			return rigidBodies[name];
		}

		/// Returns correct Joint with the given key
		std::shared_ptr< Joint > GetJoint(std::string name)
		{
			if (!joints.count(name))
				return nullptr;
			return joints[name];
		}

		/// Reset Flag (Can't reset if Physics Step is working)
		bool													toReset = false;

		/// Only Render Visible GameObject
		bool													isVisible = true;

	protected:

		/// RigidBody Container with names
		std::map< std::string, std::shared_ptr< RigidBody >>	rigidBodies;
		/// Joint Container with names
		std::map< std::string, std::shared_ptr< Joint >>		joints;

	};

}