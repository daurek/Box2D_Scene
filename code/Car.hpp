/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Car
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Project
#include "GameObject.hpp"
#include "ParticleEmitter.hpp"

namespace rigid
{
	/// Car that the player drives equiped with a water thrower
	class Car : public GameObject
	{

	public:

		using GameObject::GameObject;

		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Render(sf::RenderWindow & window) override;
		virtual void Reset() override;
		virtual void StartContact(GameObject * contactBody) {};
		virtual void EndContact(GameObject * contactBody) {};

		/// Is the water thrower enabled
		bool							isWaterEnabled = false;

	private:

		/// Caching water rigidbody
		std::shared_ptr< RigidBody >	water;
		/// Caching chassis rigidbody
		std::shared_ptr< RigidBody >	chassis;

		/// Caching joints to drive
		b2RevoluteJoint *				wheel1Joint;
		b2RevoluteJoint *				wheel2Joint;
		b2RevoluteJoint *				closerJoint;

		/// Water thrower
		std::shared_ptr< CircleParticleEmitter > waterParticles;

	};

	
	

}