/// ----------------------------------------------------------------------------------------------------------------------
/// BOX2D SCENE
/// \class rigid::Goal
///
/// \author Ilyass Sofi Hlimi
/// \date 22/04/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#pragma once

/// Project
#include "GameObject.hpp"
#include "ParticleEmitter.hpp"

namespace rigid
{
	/// Goal class that stores a timer with particles
	class Goal : public GameObject
	{

	public:

		using GameObject::GameObject;

		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Render(sf::RenderWindow & window) override;
		virtual void Reset() override;
		virtual void StartContact(GameObject * contactBody) override;
		virtual void EndContact(GameObject * contactBody) {};

	private:

		std::shared_ptr< CircleParticleEmitter >	winParticles;
		/// If the Car has reached the Goal
		bool										hasFinished = false;
		/// Max time used for timer purposes
		float										maxTime = 2;
		float										currentTime = 0;

	};

	
	

}