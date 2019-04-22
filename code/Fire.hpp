/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Fire
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

// Project
#include "GameObject.hpp"
#include "Scene.hpp"
#include "ParticleEmitter.hpp"

namespace rigid
{
	/// Fire that resets the scene if not put out with water 
	class Fire : public GameObject
	{
	public:

		using GameObject::GameObject;

		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Render(sf::RenderWindow & window) override;
		virtual void Reset() override;
		virtual void StartContact(GameObject * contactBody) override;
		virtual void EndContact(GameObject * contactBody) {};

		/// Scene Reference in order to reset scene
		Scene * scene;

	private:

		/// Fire Particles
		std::shared_ptr< CircleParticleEmitter >	fireParticles;

		/// Caching fire RigidBody
		std::shared_ptr< RigidBody >				fire;

		/// Fire has finished
		bool										isFinished = false;
	};

	
	

}